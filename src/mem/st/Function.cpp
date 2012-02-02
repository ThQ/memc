#include "mem/st/Function.hpp"

namespace mem { namespace st {


Function::Function ()
{
   this->_kind = FUNCTION;
   this->_return_type = NULL;
}

void
Function::print ()
{
   this->print_depth();
   printf("<Function[%s :", this->get_qualified_name().c_str());
   if (this->_return_type != NULL)
   {
      printf("%s", this->_return_type->get_qualified_name().c_str());
   }
   else
   {
      printf("?");
   }
   printf("]>\n");
   std::map<std::string, Symbol*>::iterator i;
   for (i = this->_children.begin() ; i != this->_children.end() ; ++ i)
   {
      i->second->print();
   }
}


} }
