#ifndef _MEM__AST__NODE__COMP_OP__HPP_
#define _MEM__AST__NODE__COMP_OP__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class BinaryOp: public Text // FIXME Inherit from Text so as to please bison
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   BinaryOp();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   inline node::Node*
   LeftNode() {return getChild(0);}

   inline node::Node*
   RightNode() {return getChild(1);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};

} } }

#endif
