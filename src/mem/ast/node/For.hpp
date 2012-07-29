#ifndef _MEM__AST__NODE__FOR__HPP_
#define _MEM__AST__NODE__FOR__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class For: public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   For();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // InitializationNode
   GETTER(InitializationNode, node::Node*) {return getChild(0);}

   // ConditionNode
   GETTER(ConditionNode, node::Node*) {return getChild(1);}

   // IterationNode
   GETTER(IterationNode, node::Node*) {return getChild(2);}

   // BlockNode
   GETTER(BlockNode, node::Node*) {return static_cast<Block*>(getChild(3));}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }


#endif
