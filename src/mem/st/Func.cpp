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
   // For some reason, parameters are not deleted from st::Symbol::~Symbol
   // before ending up here
   // But if we delete them, it will crash (SEGFAULT), should investigate
   for (size_t i = 0; i < _params.size(); ++i)
   {
      //delete _params[i];
   }
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
