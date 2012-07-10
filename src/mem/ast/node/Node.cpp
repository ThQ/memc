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
   _md = NULL;
   _next = NULL;
   _parent = NULL;
   _position = NULL;
   _prev = 0;
   _type = 0;
}

Node::Node (unsigned int type)
{
   _bound_type = NULL;
   _child_count = 0;
   _depth = 0;
   _exp_type = NULL;
   _first_child = 0;
   _last_child = 0;
   _md = NULL;
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
Node::getChild (unsigned int i)
{
   Node* res = _first_child;
   for(unsigned int j = 0; j < i && res != NULL; ++j)
   {
      res = res->_next;
   }
   return res;
}

const char*
Node::get_type_name (unsigned int type)
{
    return mem::parser::node_names[type];
}

bool
Node::isText ()
{
   switch (_type)
   {
      case MEM_NODE_TEXT:
      case MEM_NODE_FUNCTION:
      case MEM_NODE_CLASS:
      case MEM_NODE_ID:
      case MEM_NODE_FINAL_ID:
         return true;
   }
   return false;
}

bool
Node::isValid ()
{
   bool valid = true;

   Node* cur_node = _first_child;
   while (cur_node != NULL)
   {
      if (cur_node->gParent() != this)
      {
         return false;
      }
      cur_node = cur_node->_next;
   }
   return valid;
}

std::vector<st::Symbol*>
Node::packChildrenExprTypes ()
{
   std::vector<st::Symbol*> expr_types;
   for (size_t i = 0 ; i < gChildCount() ; ++i)
   {
      assert(getChild(i)->gExprType() != NULL);
      expr_types.push_back(getChild(i)->gExprType());
   }
   return expr_types;
}

void
Node::pushChild (Node* n)
{
   if (n != NULL)
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
      n->sDepth(_depth + 1);
      ++_child_count;
   }
}

void
Node::sDepth (unsigned long depth)
{
   _depth = depth;
   Node* node = _first_child;
   while (node != NULL)
   {
      node->sDepth(depth + 1);
      node = node->_next;
   }
}

void
Node::sPosition (fs::position::Range* pos)
{
   assert(pos != NULL);
   _position = pos;
}

bool
Node::replaceChild (Node* search, Node* replace)
{
   Node* cur = _first_child;
   while (cur != NULL)
   {
      if (cur == search)
      {
         cur->_prev->_next = replace;
         if (cur->_next != NULL)
         {
            cur->_next->_prev = replace;
         }
         return true;
      }
      cur = cur->_next;
   }
   return false;
}

void
Node::unlink ()
{
   _parent = NULL;
   _last_child = NULL;
   _first_child = NULL;
   _prev = NULL;
   _next = NULL;
}


} } }
