#include "mem/st/Class.hpp"


namespace mem { namespace st {


Class::Class ()
{
   this->_kind = CLASS;
   //this->_instance_type = NULL;
}

Class::~Class ()
{
   /*
   if (this->_instance_type != NULL)
   {
      delete this->_instance_type;
   }
   */
}
/*
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
*/

} }
