#ifndef _MEM__AST__MACRO__MACRO__HPP_
#define _MEM__AST__MACRO__MACRO__HPP_


#include <vector>
#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Call.hpp"
#include "mem/st/Macro.hpp"


namespace mem { namespace ast { namespace macro {


class Macro
{
   public:

   virtual st::Macro*
   getSymbol () {return NULL;}

   virtual node::Node*
   expand (node::Call* n) {return NULL;}
};

} } }

#endif
