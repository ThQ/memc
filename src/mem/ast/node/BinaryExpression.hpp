#ifndef _MEM__AST__NODE__BINARY_EXPRESSION__HPP_
#define _MEM__AST__NODE__BINARY_EXPRESSION__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class BinaryExpression : public Text
{
   public: BinaryExpression ();
   public: BinaryExpression (char* op, size_t op_len, Node* left_node, Node* right_node);

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}
};


} } }

#endif
