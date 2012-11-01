#include "mem/ast/node/FuncType.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

FuncType::FuncType()
{
   _params_node = NULL;
   _type = FuncType::kTYPE;
   _return_type_node = NULL;
}

FuncType::~FuncType ()
{
   delete _params_node;
   delete _return_type_node;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
FuncType::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _params_node;
      case 1: return _return_type_node;
   }
   return NULL;
}

void
FuncType::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setParamsNode(n);break;
      case 1: setReturnTypeNode(n);break;
   }
}


} } }
