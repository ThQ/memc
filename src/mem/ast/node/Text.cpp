#include "mem/ast/node/Text.hpp"

namespace mem { namespace ast { namespace node {


Text::Text ()
{
   _type = MEM_NODE_TEXT;
   _value.assign("");
}

Text::Text (unsigned int type)
{
   _type = type;
   _value.assign("");
}

void
Text::sValue (const char* value)
{
   _value.assign(value);
}

void
Text::sValue (const char* value, size_t len)
{
   _value.assign(value, len);
}

void
Text::sValue (std::string value)
{
   _value.assign(value);
}


} } }
