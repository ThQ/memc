#include "mem/st/Class.hpp"


namespace mem { namespace st {


Class::Class ()
{
   this->_kind = CLASS;
   this->_instance_type = NULL;
}

Class::~Class ()
{
   if (this->_instance_type != NULL)
   {
      delete this->_instance_type;
   }
}

Instance*
Class::g_instance_type ()
{
   if (this->_instance_type == NULL)
   {
      this->_instance_type = new Instance();
      this->_instance_type->set_type(this);
   }
   return this->_instance_type;
}

/*
void
Class::print ()
{
   this->print_depth();
   printf("[Class:%s]\n", this->get_qualified_name().c_str());
   std::map<std::string, Symbol*>::iterator i;
   for (i = this->_children.begin() ; i != this->_children.end() ; ++ i)
   {
      i->second->print();
   }
}
*/

} }
