#include "mem/ast/node/ArrayType.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

ArrayType::ArrayType ()
{
   _length_node = NULL;
   _type = ArrayType::kTYPE;
   _type_node = NULL;
}

ArrayType::~ArrayType ()
{
   delete _length_node;
   delete _type_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
ArrayType::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _length_node;
      case 1: return _type_node;
   }
   return NULL;
}

void
ArrayType::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: _length_node = n;
      case 1: _type_node = n;
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
