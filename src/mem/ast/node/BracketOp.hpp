#ifndef _MEM__AST__NODE__BRACKET_OP__HPP_
#define _MEM__AST__NODE__BRACKET_OP__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class BracketOp: public Node
{
   public:
   static const int kTYPE = Kind::BRACKET_OP;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   BracketOp ();

   // Destructor
   virtual
   ~BracketOp ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ValueNode
   GETTER(ValueNode, node::Node*) {return _value_node;}
   SETTER(ValueNode, node::Node*)
   {
      _value_node = val;
      if (val != NULL) val->setParent(this);
   }

   // IndexNode
   GETTER(IndexNode, node::Node*) {return _index_node;}
   SETTER(IndexNode, node::Node*)
   {
      _index_node = val;
      if (val != NULL) val->setParent(this);
   }

   virtual
   GETTER(MemorySize, int) {return sizeof(BracketOp);}


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

   node::Node* _value_node;
   node::Node* _index_node;
};

} } }

#endif
