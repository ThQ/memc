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
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // LeftNode
   GETTER(LeftNode, node::Node*) {return getChild(0);}

   // RightNode
   GETTER(RightNode, node::Node*) {return getChild(1);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};

Dot*
castToDot (Node* s);

} } }

#endif
