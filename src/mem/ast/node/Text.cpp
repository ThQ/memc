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
