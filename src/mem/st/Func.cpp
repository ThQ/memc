#include "mem/st/Func.hpp"

namespace mem { namespace st {


Func::Func ()
{
   _kind = FUNCTION;
   _is_entry_point = false;
   //_overloaded_func = NULL;
   _return_type = NULL;
}

Func::~Func ()
{
   // We don't delete the parameters here because they are added as st::Func
   // children and will be deleted from st::Symbol.
}

st::Arg*
Func::addParam (std::string name, st::Type* ty)
{
   assert (ty != NULL);

   st::Arg* param = new st::Arg();
   param->setType(ty);
   param->setName(name);
   _params.push_back(param);

   return param;
}

st::Var*
Func::getParam (int i)
{
   return _params[i];
}

} }
