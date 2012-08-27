#include "mem/ast/node/VarDecl.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

VarDecl::VarDecl ()
{
   _name_node = NULL;
   _type = VarDecl::kTYPE;
   _type_node = NULL;
   _value_node = NULL;
}

VarDecl::~VarDecl ()
{
   delete _name_node;
   delete _type_node;
   delete _value_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
VarDecl::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _name_node;
      case 1: return _type_node;
      case 2: return _value_node;
   }
   return NULL;
}

void
VarDecl::isValid (NodeValidator* v)
{
   // Check self
   Node::isValid(v);
   v->ensure(hasExprType(), "VarDecl must have an expression type");
   v->ensure(hasBoundSymbol(), "VarDecl must have a bound symbol");

   v->ensure(NameNode() != NULL, "VarDecl must have a name node");

   if (NameNode() != NULL)
   {
      // Check NAME node
      v->ensure(NameNode()->hasBoundSymbol(), "VarDecl : Name node must have a bound symbol");
   }

   if (TypeNode() != NULL)
   {
      // Check TYPE node
      v->ensure(TypeNode()->hasExprType(), "VarDecl : Type node must have an expression type");
      v->ensure(TypeNode()->hasBoundSymbol(), "VarDecl : Type node must have a bound symbol");
   }
}

void
VarDecl::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setNameNode(node::cast<FinalId>(n)); break;
      case 1: setTypeNode(n); break;
      case 2: setValueNode(n); break;
   }
}


} } }
