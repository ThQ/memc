#include "mem/ast/node/LeftUnary.hpp"

namespace mem { namespace ast { namespace node {


LeftUnary::LeftUnary ()
{
   this->_type = MEM_NODE_LEFT_UNARY;
}

LeftUnary::LeftUnary (char* op, size_t op_len, Node* node)
{
   this->_type = MEM_NODE_LEFT_UNARY;
   this->set_value(op, op_len);
   this->push_child(node);
}


} } }
