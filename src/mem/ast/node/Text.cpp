#include "mem/ast/node/Text.hpp"

namespace mem { namespace ast { namespace node {


Text::Text ()
{
   this->_type = MEM_NODE_TEXT;
   this->_value.assign("");
}

Text::Text (unsigned int type)
{
   this->_type = type;
   this->_value.assign("");
}

void
Text::dump_self ()
{
   this->dump_depth();
   printf("%s:%s",
      Node::get_type_name(this->_type),
      this->_value.c_str());

   if (this->_bound_type != NULL || this->_exp_type != NULL)
   {
      printf(" (");
      if (this->_bound_type != NULL)
      {
         printf("%s", this->_bound_type->get_qualified_name().c_str());
      }
      else
      {
         printf(" ");
      }
      printf(" -> ");
      if (this->_exp_type != NULL)
      {
         printf("%s", this->_exp_type->get_qualified_name().c_str());
      }
      else
      {
         printf(" ");
      }
      printf(")");
   }
   if (this->_position != NULL)
   {
      printf(" @%s:%d:%d", this->_position->_file->_path.c_str(), this->_position->_line, this->_position->_column_start);
   }
   printf("\n");
}

void
Text::set_value (const char* value)
{
   this->_value.assign(value);
}

void
Text::set_value (const char* value, size_t len)
{
   this->_value.assign(value, len);
}

void
Text::set_value (std::string value)
{
   this->_value.assign(value);
}


} } }
