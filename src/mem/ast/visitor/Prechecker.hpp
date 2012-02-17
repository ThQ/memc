#ifndef _MEM__AST__VISITOR__PRECHECKER__HPP_
#define _MEM__AST__VISITOR__PRECHECKER__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Text.hpp"
#include "mem/ast/visitor/Visitor.hpp"


namespace mem { namespace ast { namespace visitor {


class Prechecker : public Visitor
{
   public: Prechecker ();

   public: virtual bool visit (node::Node* node);
};


} } }

#endif
