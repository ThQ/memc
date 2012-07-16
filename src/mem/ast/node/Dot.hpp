#ifndef _MEM__AST__NODE__DOT__HPP_
#define _MEM__AST__NODE__DOT__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class Dot: public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Dot();


   //--------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   //--------------------------------------------------------------------------
   public:

   inline node::Node*
   LeftNode() {return getChild(0);}

   inline node::Node*
   RightNode() {return getChild(1);}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};

} } }

#endif
