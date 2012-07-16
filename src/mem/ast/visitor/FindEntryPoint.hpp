#ifndef _MEM__AST__VISITOR__FIND_ENTRY_POINT__HPP_
#define _MEM__AST__VISITOR__FIND_ENTRY_POINT__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Text.hpp"
#include "mem/ast/visitor/Visitor.hpp"


namespace mem { namespace ast { namespace visitor {


class FindEntryPoint : public Visitor
{
   public: st::Symbol* _entry_point;

   public: FindEntryPoint();
   public: virtual bool tearDown ();
   public: virtual bool visit (node::Node* node);
};


} } }

#endif
