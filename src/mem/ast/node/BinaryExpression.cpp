#include "mem/ast/node/BinaryExpression.hpp"

namespace mem { namespace ast { namespace node {


BinaryExpression::BinaryExpression ()
{
   this->_type = MEM_NODE_GROUP;
}

BinaryExpression::BinaryExpression (char* op, size_t op_len, Node* left_node, Node* right_node)
{
   this->_type = MEM_NODE_GROUP;
   this->sValue(op, op_len);
   this->pushChildren(left_node, right_node);
}


} } }
