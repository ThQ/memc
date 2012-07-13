#include "mem/st/Var.hpp"

namespace mem { namespace st {


Var::Var ()
{
   _kind = VAR;
   _type = NULL;
}

Var::Var (std::string name, Type* type)
{
   _kind = VAR;
   _name.assign(name);
   _type = type;
}

Var*
Var::create (std::string name, Type* ty)
{
   Var* var = new st::Var();
   var->sName(name);
   var->sType(ty);
   return var;
}

Symbol*
Var::gEvalType ()
{
   return _type;
}

Symbol*
Var::gExprType ()
{
   return _type;
}


} }
