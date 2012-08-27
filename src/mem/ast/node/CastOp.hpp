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
   static const int kTYPE = Kind::OP_CAST;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   CastOp ();

   // Destructor
   virtual
   ~CastOp ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ValueNode
   GETTER(ValueNode, node::Node*) {return _value_node;}
   SETTER(ValueNode, node::Node*) {_value_node = val;}

   // TypeNode
   GETTER(TypeNode, node::Node*) {return _type_node;}
   SETTER(TypeNode, node::Node*) {_type_node = val;}

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}


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
   public:

   Node* _type_node;
   Node* _value_node;
};

} } }

#endif
