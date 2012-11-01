#ifndef _MEM__AST__NODE__UNARY_OP__HPP_
#define _MEM__AST__NODE__UNARY_OP__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


// A unary operator
class UnaryOp : public Node
{
   public:
   static const int kTYPE = MetaKind::UNARY_OPERATOR;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   UnaryOp ();

   // Destructor
   virtual
   ~UnaryOp ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER (ChildCount, size_t) {return 1;}

   virtual
   GETTER (MemorySize, int) {return sizeof(UnaryOp);}

   // ValueNode
   GETTER (ValueNode, Node*) {return _nodeValue;}
   SETTER (ValueNode, Node*)
   {
      _nodeValue = val;
      if (val != NULL) val->setParent(this);
   }


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

   Node* _nodeValue;
};


} } }

#endif
