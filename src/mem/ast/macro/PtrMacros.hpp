#ifndef _MEM__AST__MACRO__PTR_MACROS__HPP_
#define _MEM__AST__MACRO__PTR_MACROS__HPP_


#include "mem/ast/node/ArrayType.hpp"
#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/New.hpp"
#include "mem/ast/node/NodeList.hpp"
#include "mem/ast/node/String.hpp"
#include "mem/ast/macro/Macro.hpp"


namespace mem { namespace ast { namespace macro {


class PtrMacros : public Macro
{
   public:

   virtual st::Macro*
   getSymbol ();

   virtual node::Node*
   expand (node::Call* n);
};


} } }

#endif
