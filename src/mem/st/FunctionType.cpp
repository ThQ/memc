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

bool
FunctionType::canCastTo (Type* dest_ty) const
{
   if (!dest_ty->isFunctionType()) return false;

   st::FunctionType* dest = static_cast<st::FunctionType*>(dest_ty);
   if (dest->ArgumentCount() != ArgumentCount()) return false;
   if (dest->ReturnType() != ReturnType()) return false;

   for (size_t i = 0; i < ArgumentCount(); ++i)
   {
      if (!getArgument(i)->canCastTo(dest->getArgument(i))) return false;
   }
   return true;
}

st::Type*
FunctionType::getArgument (int i) const
{
   return _arguments[i];
}

bool
FunctionType::isLike (TypeVector arguments, Type* return_type)
{
   if (_return_type != return_type) return false;
   if (_arguments.size() != arguments.size()) return false;

   for (size_t i = 0; i < arguments.size(); ++i)
   {
      if (arguments[i] != _arguments[i]) return false;
   }
   return true;
}

bool
FunctionType::isOverridenCandidate (FunctionType* candidate)
{
   if (candidate == NULL) return false;
   if (_arguments.size() != candidate->Arguments().size()) return false;
   if (_return_type != candidate->ReturnType()) return false;

   for (size_t i = 0; i < _arguments.size(); ++i)
   {
      if (!_arguments[i]->canCastTo(candidate->getArgument(i)))
      {
         return false;
      }
   }
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

FunctionType*
castToFunctionType (Symbol* s)
{
   assert (s->isFunctionType());
   return static_cast<FunctionType*>(s);
}
} }
