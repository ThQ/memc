#include "mem/st/FunctionType.hpp"

namespace mem { namespace st {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

FunctionType::FunctionType ()
{
   _byte_size = sizeof(void*);
   _functor_type = NULL;
   _kind = FUNCTION_TYPE;
   _return_type = NULL;
}

FunctionType::~FunctionType ()
{
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
FunctionType::addArgument (st::Type* ty)
{
   _arguments.push_back(ty);
   _computeName();
}

void
FunctionType::addArguments (TypeVector tys)
{
   for (size_t i = 0; i < tys.size(); ++i)
   {
      addArgument(tys[i]);
   }
}

st::Type*
FunctionType::getArgument (int i)
{
   return _arguments[i];
}

bool
FunctionType::isLike (TypeVector arguments, Type* return_type)
{
   DEBUG_PRINTF("isLike(%d) %s\n", arguments.size(), gQualifiedNameCstr());

   if (_return_type != return_type) return false;
   if (_arguments.size() != arguments.size()) return false;

   for (size_t i = 0; i < arguments.size(); ++i)
   {
      if (arguments[i] != _arguments[i]) return false;
   }
   DEBUG_PRINT("yes\n");
   return true;
}

//-----------------------------------------------------------------------------
// PROTECTED FUNCTIONS
//-----------------------------------------------------------------------------

void
FunctionType::_computeName ()
{
   _name = "(";
   for (size_t i = 0; i < ArgumentCount(); ++i)
   {
      if (i != 0) _name += ",";
      _name += _arguments[i]->gQualifiedName();
   }
   _name += ") -> ";
   _name += _return_type->gQualifiedName();
}

} }
