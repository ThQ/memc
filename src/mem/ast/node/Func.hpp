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
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   node::Block*
   BodyNode ();

   Node*
   ParamsNode ();

   Node*
   ReturnTypeNode ();


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   bool
   isVirtual ();
};


} } }

#endif
