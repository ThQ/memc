#include "mem/st/Var.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTORS
//-----------------------------------------------------------------------------

Var::Var ()
{
   _constant_value = NULL;
   _kind = VAR;
   _is_global = false;
   _is_constant = false;
   _type = NULL;
}

Var::Var (std::string name, class Type* type)
{
   _constant_value = NULL;
   _kind = VAR;
   _is_global = false;
   _is_constant = false;
   _name.assign(name);
   _type = type;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Var*
Var::create (std::string name, class Type* ty)
{
   Var* var = new st::Var();
   var->setName(name);
   var->setType(ty);
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
