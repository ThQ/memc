#include "mem/st/Func.hpp"

namespace mem { namespace st {


Func::Func ()
{
   _kind = FUNCTION;
   _is_entry_point = false;
   _overloaded_func = NULL;
   _return_type = NULL;
}

Func::~Func ()
{
   for (size_t i = 0; i < _params.size(); ++i)
   {
      assert (_params[i] != NULL);
      //delete _params[i];
   }
}

st::Var*
Func::addParam (std::string name, st::Type* ty)
{
   assert (ty != NULL);

   // FIXME Who deletes that ?
   st::Var* param = new st::Var(name, ty);
   _params.push_back(param);
   return param;
}

st::Var*
Func::getParam (int i)
{
   return _params[i];
}

} }
