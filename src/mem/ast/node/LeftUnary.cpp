#include "mem/ast/node/LeftUnary.hpp"

namespace mem { namespace ast { namespace node {


LeftUnary::LeftUnary ()
{
   this->_type = MEM_NODE_LEFT_UNARY;
}

LeftUnary::LeftUnary (char* op, size_t op_len, Node* node)
{
   this->_type = MEM_NODE_LEFT_UNARY;
   this->sValue(op, op_len);
   this->pushChild(node);
}


} } }
