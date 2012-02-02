#ifndef _MEM__AST__VISITOR__FIND_USE__HPP_
#define _MEM__AST__VISITOR__FIND_USE__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Text.hpp"
#include "mem/ast/visitor/Visitor.hpp"


namespace mem { namespace ast { namespace visitor {


class FindUse : public Visitor
{
   public: std::vector<std::string> _uses;
   public: virtual bool visit (node::Node* node);
};


} } }

#endif
