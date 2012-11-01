#ifndef _MEM__AST__NODE__FOR__HPP_
#define _MEM__AST__NODE__FOR__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class For: public Node
{
   public:
   static const int kTYPE = MetaKind::FOR;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   For();

   // Destructor
   virtual
   ~For ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // BlockNode
   GETTER(BlockNode, node::Block*) {return _nodeBlock;}
   SETTER(BlockNode, node::Block*)
   {
      _nodeBlock = val;
      if (val != NULL) val->setParent(this);
   }

   // ChildCount
   GETTER(ChildCount, size_t) {return 4;}

   // ConditionNode
   GETTER(ConditionNode, node::Node*) {return _nodeCondition;}
   SETTER(ConditionNode, node::Node*)
   {
      _nodeCondition = val;
      if (val != NULL) val->setParent(this);
   }

   // InitializationNode
   GETTER(InitializationNode, node::Node*) {return _nodeInitialization;}
   SETTER(InitializationNode, node::Node*)
   {
      _nodeInitialization = val;
      if (val != NULL) val->setParent(this);
   }

   // IterationNode
   GETTER(IterationNode, node::Node*) {return _nodeIteration;}
   SETTER(IterationNode, node::Node*)
   {
      _nodeIteration = val;
      if (val != NULL) val->setParent(this);
   }

   // MemorySize
   virtual
   GETTER(MemorySize, int) {return sizeof(For);}


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   getChild (size_t i) const;

   virtual void
   isValid (NodeValidator* v);

   virtual void
   setChild (size_t i, Node* n);


   //==========================================================================
   // FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   Block* _nodeBlock;
   Node* _nodeCondition;
   Node* _nodeInitialization;
   Node* _nodeIteration;
};

} } }


#endif
