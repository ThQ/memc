#ifndef _MEM__AST__NODE__FOR__HPP_
#define _MEM__AST__NODE__FOR__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class For: public Node
{
   public:
   static const int kTYPE = Kind::FOR;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   For();

   // Destructor
   virtual
   ~For ();

   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // BlockNode
   GETTER(BlockNode, node::Block*) {return _block_node;}
   SETTER(BlockNode, node::Block*) {_block_node = val;}

   // ChildCount
   GETTER(ChildCount, size_t) {return 4;}

   // ConditionNode
   GETTER(ConditionNode, node::Node*) {return _condition_node;}
   SETTER(ConditionNode, node::Node*) {_condition_node = val;}

   // InitializationNode
   GETTER(InitializationNode, node::Node*) {return _initialization_node;}
   SETTER(InitializationNode, node::Node*) {_initialization_node = val;}

   // IterationNode
   GETTER(IterationNode, node::Node*) {return _iteration_node;}
   SETTER(IterationNode, node::Node*) {_iteration_node = val;}

   // MemorySize
   virtual
   GETTER(MemorySize, int) {return sizeof(For);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   getChild (size_t i) const;

   virtual void
   isValid (NodeValidator* v);

   virtual void
   setChild (size_t i, Node* n);

   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   Block* _block_node;
   Node* _condition_node;
   Node* _initialization_node;
   Node* _iteration_node;
};

} } }


#endif
