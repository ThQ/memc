#ifndef _MEM__AST__NODE__CAST_OP__HPP_
#define _MEM__AST__NODE__CAST_OP__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {

// A node to represent cast operations
//
// Ex:
//    <value> :<type>
class CastOp: public Node
{
   public:
   static const int kTYPE = MetaKind::OP_CAST;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   CastOp ();

   // Destructor
   virtual
   ~CastOp ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ValueNode
   GETTER(ValueNode, node::Node*) {return _nodeValue;}
   SETTER(ValueNode, node::Node*)
   {
      _nodeValue = val;
      if (val != NULL) val->setParent(this);
   }

   // TypeNode
   GETTER(TypeNode, node::Node*) {return _nodeType;}
   SETTER(TypeNode, node::Node*)
   {
      _nodeType = val;
      if (val != NULL) val->setParent(this);
   }

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}


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
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   Node* _nodeType;
   Node* _nodeValue;
};

} } }

#endif
