#include "mem/ast/node/ArrayType.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

ArrayType::ArrayType ()
{
   _nodeLength = NULL;
   _nodeType = NULL;
   _type = ArrayType::kTYPE;
}

ArrayType::~ArrayType ()
{
   delete _nodeLength;
   delete _nodeType;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
ArrayType::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeLength;
      case 1: return _nodeType;
   }
   return NULL;
}

void
ArrayType::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setLengthNode(n);
      case 1: setTypeNode(n);
   }
}

void
ArrayType::isValid (NodeValidator* v)
{
   Node::isValid(v);

   v->ensure(TypeNode() != NULL, "Array must have a type node");

   if (TypeNode() != NULL)
   {
      v->ensure(TypeNode()->hasBoundSymbol(), "ARRAY : type node must have a bound symbol");
   }
}


} } }
