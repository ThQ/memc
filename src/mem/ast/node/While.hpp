#ifndef _MEM__AST__NODE__WHILE__HPP_
#define _MEM__AST__NODE__WHILE__HPP_


#include <string>
#include "mem/ast/node/Block.hpp"


namespace mem { namespace ast { namespace node {


class While : public Node
{
   public:
   static const int kTYPE = MetaKind::WHILE;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   While ();

   // Destructor
   ~While ();


   //--------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ChildCount
   virtual
   GETTER (ChildCount, size_t) {return 2;}

   // ConditionNode
   GETTER (ConditionNode, Node*) {return _condition_node;}
   SETTER (ConditionNode, Node*)
   {
      _condition_node = val;
      if (val != NULL) val->setParent(this);
   }

   // BodyNode
   GETTER (BlockNode, Block*) {return _block_node;}
   SETTER (BlockNode, Block*)
   {
      _block_node = val;
      if (val != NULL) val->setParent(this);
   }

   virtual
   GETTER (MemorySize, int) {return sizeof(While);}


   //--------------------------------------------------------------------------
   // PUBLIC METHODS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   getChild (size_t i) const;

   virtual void
   isValid (NodeValidator* v);

   virtual void
   setChild (size_t i, Node* n);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   Node* _condition_node;
   Block* _block_node;
};


} } }


#endif
