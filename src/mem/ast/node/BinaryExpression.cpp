#include "mem/ast/node/BinaryExpression.hpp"

namespace mem { namespace ast { namespace node {


BinaryExpression::BinaryExpression ()
{
   this->_type = MEM_NODE_GROUP;
}

BinaryExpression::BinaryExpression (char* op, size_t op_len, Node* left_node, Node* right_node)
{
   this->_type = MEM_NODE_GROUP;
   this->set_value(op, op_len);
   this->push_children(left_node, right_node);
}


} } }
