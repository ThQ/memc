#ifndef _MEM__AST__NODE__COMP_OP__HPP_
#define _MEM__AST__NODE__COMP_OP__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class BinaryOp: public Text // FIXME Inherit from Text so as to please bison
{
   public:
   static const int kTYPE = MetaKind::BINARY_OPERATOR;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   BinaryOp ();

   // Destructor
   ~BinaryOp ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return 2;}

   GETTER (LeftNode, node::Node*) {return _left_node;}
   SETTER (LeftNode, node::Node*)
   {
      _left_node = val;
      if (val != NULL) val->setParent(this);
   }

   GETTER (RightNode, node::Node*) {return _right_node;}
   SETTER (RightNode, node::Node*)
   {
      _right_node = val;
      if (val != NULL) val->setParent(this);
   }

   virtual
   GETTER(MemorySize, int) {return sizeof(BinaryOp);}


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
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   node::Node* _left_node;
   node::Node* _right_node;
};

} } }

#endif
