#include "mem/st/Var.hpp"

namespace mem { namespace st {


Var::Var ()
{
   this->_kind = VAR;
   this->_type = NULL;
}

Var::Var (std::string name, Type* type)
{
   this->_kind = VAR;
   this->_name = name;
   this->_type = type;
}

void
Var::sType (Symbol* type)
{
   this->_type = static_cast<Type*>(type);
}


} }
