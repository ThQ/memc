#include "mem/ast/node/Field.hpp"

namespace mem { namespace ast { namespace node {


Field::Field ()
{
   this->_type = MEM_NODE_FIELD;
}

std::string
Field::get_type_name ()
{
   node::Type* type = static_cast<node::Type*>(this->get_child(1));
   return type->_value;
}


} } }
