#ifndef _MEM__AST__VISITOR__DUMPER__HPP_
#define _MEM__AST__VISITOR__DUMPER__HPP_


#include <iostream>
#include <string>
#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/visitor/Visitor.hpp"



namespace mem { namespace ast { namespace visitor {


class Dumper : public Visitor
{
   public: std::ostream* _out;

   //--------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   //--------------------------------------------------------------------------
   public:

   void
   Out (std::ostream* out) {_out = out;}
};


} } }


#endif
