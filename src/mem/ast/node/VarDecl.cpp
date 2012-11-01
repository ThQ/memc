#include "mem/ast/node/VarDecl.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

VarDecl::VarDecl ()
{
   _nodeName = NULL;
   _nodeType = NULL;
   _nodeValue = NULL;
   _type = VarDecl::kTYPE;
}

VarDecl::~VarDecl ()
{
   delete _nodeName;
   delete _nodeType;
   delete _nodeValue;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
VarDecl::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeName;
      case 1: return _nodeType;
      case 2: return _nodeValue;
   }
   assert(false);
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
   assert(false);
}


} } }
