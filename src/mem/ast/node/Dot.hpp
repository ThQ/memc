#ifndef _MEM__AST__NODE__DOT__HPP_
#define _MEM__AST__NODE__DOT__HPP_


#include "mem/ast/node/Node.hpp"


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

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}

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
