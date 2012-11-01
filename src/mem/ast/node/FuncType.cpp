#include "mem/ast/node/FuncType.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

FuncType::FuncType()
{
   _nodeParams = NULL;
   _nodeReturnType = NULL;
   _type = FuncType::kTYPE;
}

FuncType::~FuncType ()
{
   delete _nodeParams;
   delete _nodeReturnType;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
FuncType::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeParams;
      case 1: return _nodeReturnType;
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
