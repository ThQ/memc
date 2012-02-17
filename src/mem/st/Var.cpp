#include "mem/st/Var.hpp"

namespace mem { namespace st {


Var::Var ()
{
   this->_kind = VAR;
   this->_type = NULL;
}

/*
void
Var::print ()
{
   this->print_depth();
   printf("[Var:%s] :%s\n",
          this->g_name_cstr(),
          (this->_type!=NULL) ? this->_type->get_qualified_name().c_str() : "?");

   std::map<std::string, Symbol*>::iterator i;
   for (i = this->_children.begin() ; i != this->_children.end() ; ++ i)
   {
      i->second->print();
   }
}
*/


void
Var::set_type (Symbol* type)
{
   this->_type = static_cast<Type*>(type);
}


} }
