#ifndef _MEM__AST__NODE__CAST_OP__HPP_
#define _MEM__AST__NODE__CAST_OP__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class CastOp: public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   CastOp();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // LeftNode
   GETTER(ValueNode, node::Node*) {return getChild(0);}

   // RightNode
   GETTER(TypeNode, node::Node*) {return getChild(1);}

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};

} } }

#endif
