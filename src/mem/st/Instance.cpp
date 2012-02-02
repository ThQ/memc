#include "mem/st/Instance.hpp"

namespace mem { namespace st {


Instance::Instance ()
{
   this->_kind = INSTANCE;
   this->_type = NULL;
}

std::string
Instance::get_qualified_name()
{
   std::string res = "InstanceOf:?";
   if (this->_type != NULL)
   {
      res = "InstanceOf:" + this->_type->get_qualified_name();
   }
   return res;
}

void
Instance::print ()
{
   this->print_depth();
   printf("<Instance:%s>\n", (this->_type!=NULL) ? this->_type->get_qualified_name().c_str() : "?");
}

void
Instance::set_type (Symbol* type)
{
   assert (type->_kind = CLASS);
   this->_type = type;
}

} }
