#ifndef _MEM__AST__VISITOR__VISITOR__HPP_
#define _MEM__AST__VISITOR__VISITOR__HPP_


#include "macro.h"
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace visitor {


class Visitor
{
   public: virtual bool visit (node::Node* node);
   public: virtual void visit_preorder (node::Node* node);
};


} } }

#endif
