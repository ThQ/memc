#ifndef _MEM__AST__NODE__FUNC__HPP_
#define _MEM__AST__NODE__FUNC__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class Func: public Text
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:
   Func();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   node::Block*
   gBodyNode ();

   Node*
   gParamsNode ();

   Node*
   gReturnTypeNode ();

   bool
   isVirtual ();
};

} } }

#endif
