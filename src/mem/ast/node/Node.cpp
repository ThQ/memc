#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Node::Node ()
{
   _bound_type = NULL;
   _exp_type = NULL;
   _parent = NULL;
   _position = NULL;
   _type = Node::kTYPE;
}

Node::~Node ()
{
   delete _position;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Node::getChild (size_t i) const
{
   return NULL;
}

const char*
Node::get_type_name (int type)
{
    return kKIND_NAMES[type];
}

bool
Node::isAssignable ()
{
   switch (Kind())
   {
      case MetaKind::FINAL_ID:
      case MetaKind::DOT:
      case MetaKind::AMPERSAND:
      case MetaKind::BRACKET_OP:
      case MetaKind::DEREF:
         return true;
   }
   return false;
}

bool
Node::isReferenceNode () const
{
   switch (Kind())
   {
      case MetaKind::ARRAY:
      case MetaKind::BRACKET_OP:
      case MetaKind::DOT:
      case MetaKind::FINAL_ID:
         return true;
      default:
         return false;
   }
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

bool
Node::replaceChild (Node* search, Node* replace)
{
   for (size_t i = 0; i < ChildCount(); ++i)
   {
      if (getChild(i) == search)
      {
         setChild(i, replace);
      }
   }
   return true;
}

void
assertKind (Node* n, int k)
{
#ifndef NDEBUG
   if (!n->isKind(k))
   {
      DEBUG_PRINTF("Node (@%p) is not a `%s' but a `%s'\n",
         n,
         Node::get_type_name(k),
         Node::get_type_name(n->Kind()));
      assert (n->isKind(k));
   }
#endif
}
} } }
