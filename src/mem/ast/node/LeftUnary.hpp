#ifndef _MEM__AST__NODE__LEFT_UNARY__HPP_
#define _MEM__AST__NODE__LEFT_UNARY__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class LeftUnary : public Text
{
   public: LeftUnary ();
   public: LeftUnary (char* op, size_t op_len, Node* node);
};


} } }

#endif
