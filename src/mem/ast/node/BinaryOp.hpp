#ifndef _MEM__AST__NODE__COMP_OP__HPP_
#define _MEM__AST__NODE__COMP_OP__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class BinaryOp: public Text // FIXME Inherit from Text so as to please bison
{
   public:
   static const int kTYPE = MetaKind::BINARY_OPERATOR;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   BinaryOp ();

   // Destructor
   virtual
   ~BinaryOp ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return 2;}

   GETTER (LeftNode, node::Node*) {return _nodeLeft;}
   SETTER (LeftNode, node::Node*)
   {
      _nodeLeft = val;
      if (val != NULL) val->setParent(this);
   }

   GETTER (RightNode, node::Node*) {return _nodeRight;}
   SETTER (RightNode, node::Node*)
   {
      _nodeRight = val;
      if (val != NULL) val->setParent(this);
   }

   virtual
   GETTER(MemorySize, int) {return sizeof(BinaryOp);}


   //==========================================================================
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   getChild (size_t i) const;

   virtual void
   isValid (NodeValidator* v);

   virtual void
   setChild (size_t i, Node* n);


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   node::Node* _nodeLeft;
   node::Node* _nodeRight;
};

} } }

#endif
