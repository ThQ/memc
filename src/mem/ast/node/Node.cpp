#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


Node::Node ()
{
   _bound_type = NULL;
   _child_count = 0;
   _depth = 0;
   _exp_type = NULL;
   _first_child = NULL;
   _last_child = NULL;
   _next = NULL;
   _parent = NULL;
   _position = NULL;
   _prev = NULL;
   _type = Kind::UNKNOWN;
}

Node::Node (unsigned int type)
{
   _bound_type = NULL;
   _child_count = 0;
   _depth = 0;
   _exp_type = NULL;
   _first_child = 0;
   _last_child = 0;
   _next = 0;
   _parent = 0;
   _position = NULL;
   _prev = 0;
   _type = type;
}

Node::~Node ()
{
   if (_first_child != NULL)
   {
      Node* cur_node = _first_child;
      Node* tmp_node = NULL;
      while (cur_node != NULL)
      {
         tmp_node = cur_node;
         cur_node = cur_node->_next;
         delete tmp_node;
      }
   }
   delete _position;
}

void
Node::eat (Node* n)
{
   if (n != NULL)
   {
       if (n->_first_child != NULL)
       {
          _first_child = n->_first_child;
       }

       if (n->_last_child != NULL)
       {
          _last_child = n->_last_child;
       }

       Node* cur_node = n->_first_child;
       while (cur_node)
       {
         cur_node->_parent = this;
         cur_node = cur_node->_next;
       }
       _child_count = n->_child_count;
       n->unlink();
   }
}

Node*
Node::getChild (unsigned int i) const
{
   Node* res = _first_child;
   for(unsigned int j = 0; j < i && res != NULL; ++j)
   {
      res = res->_next;
   }
   return res;
}

const char*
Node::get_type_name (int type)
{
    return kKIND_NAMES[type];
}

void
Node::insertChild (Node* n)
{
   DEBUG_REQUIRE (n != NULL);

   n->_parent = this;
   if (_first_child != NULL)
   {
      _first_child->_prev = n;
      n->_next = _first_child;
   }
   _first_child = n;
   n->_depth = this->_depth + 1;
   _child_count ++;
}

bool
Node::isAssignable ()
{
   switch (Kind())
   {
      case Kind::FINAL_ID:
      case Kind::DOT:
      case Kind::AMPERSAND:
      case Kind::BRACKET_OP:
      case Kind::DEREF:
         return true;
   }
   return false;
}

bool
Node::isReferenceNode () const
{
   switch (Kind())
   {
      case Kind::ARRAY:
      case Kind::BRACKET_OP:
      case Kind::DOT:
      case Kind::FINAL_ID:
         return true;
      default:
         return false;
   }
}

bool
Node::isText ()
{
   switch (Kind())
   {
      case Kind::TEXT:
      case Kind::FUNCTION:
      case Kind::CLASS:
      case Kind::ID:
      case Kind::FINAL_ID:
         return true;
   }
   return false;
}

void
Node::isValid (NodeValidator* v)
{
   v->ensure(Parent() != this, "Node cannot have itself as parent");
}

st::TypeVector
Node::packChildrenExprTypes ()
{
   st::TypeVector expr_types;
   for (size_t i = 0 ; i < ChildCount() ; ++i)
   {
      assert(getChild(i)->ExprType() != NULL);
      expr_types.push_back(getChild(i)->ExprType());
   }
   return expr_types;
}

void
Node::pushChild (Node* n)
{
   if (n != NULL && n != this)
   {
      if (_first_child == 0)
      {
         _first_child = n;
      }
      if (_last_child != 0)
      {
         _last_child->_next = n;
      }
      n->_parent = this;
      n->_prev = _last_child;
      _last_child = n;
      n->Depth(_depth + 1);
      ++_child_count;
   }

   assert(n != this);
}

void
Node::Depth (unsigned long depth)
{
   /*
   //_depth = depth;
   Node* node = _first_child;
   while (node != NULL)
   {
      assert (node != this);

      //node->Depth(depth + 1);
      node = node->_next;
   }
   */
}

Node*
Node::removeChild (Node* search)
{
   Node* cur = _first_child;
   while (cur != NULL)
   {
      if (cur == search)
      {
         if (search->_prev != NULL)
         {
            search->_prev->_next = search->_next;
         }
         else
         {
            // Search was the first child
            search->_parent->_first_child = search->_next;
         }

         if (search->_next != NULL)
         {
            search->_next->_prev = search->_prev;
         }
         else
         {
            // Search was the last child
            search->_parent->_last_child = search->_prev;
         }

         _child_count--;
         return search;
      }

      cur = cur->_next;
   }
   return NULL;
}

bool
Node::replaceChild (Node* search, Node* replace)
{
   Node* cur = _first_child;
   while (cur != NULL)
   {
      if (cur == search)
      {
         if (search->_prev != NULL)
         {
            search->_prev->_next = replace;
            replace->_prev = search->_prev;
         }
         else
         {
            // Search was the first child of its parent
            search->Parent()->_first_child = replace;
         }

         if (search->_next != NULL)
         {
            search->_next->_prev = replace;
            replace->_next = search->_next;
         }
         else
         {
            search->Parent()->_last_child = replace;
         }

         replace->_parent = search->_parent;
         search->_parent = NULL;
         return true;
      }
      cur = cur->_next;
   }
   return false;
}

void
Node::unlink ()
{
   _child_count = 0;
   _parent = NULL;
   _last_child = NULL;
   _first_child = NULL;
   _prev = NULL;
   _next = NULL;
}

void
Node::unlinkChildren ()
{
   _child_count = 0;
   _last_child = NULL;
   _first_child = NULL;
}

void
assertKind (Node* n, int k)
{
#ifndef NDEBUG
   if (!n->isKind(k))
   {
      DEBUG_PRINTF("Node (@%x) is not a `%s' but a `%s'\n",
         (int)n,
         Node::get_type_name(k),
         Node::get_type_name(n->Kind()));
      assert (n->isKind(k));
   }
#endif
}
} } }
