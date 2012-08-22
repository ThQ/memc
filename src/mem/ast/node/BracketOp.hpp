#ifndef _MEM__AST__NODE__BRACKET_OP__HPP_
#define _MEM__AST__NODE__BRACKET_OP__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class BracketOp: public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   BracketOp();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ValueNode
   GETTER(ValueNode, node::Node*) {return getChild(0);}

   // IndexNode
   GETTER(IndexNode, node::Node*) {return getChild(1);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};

} } }

#endif
