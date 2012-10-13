#ifndef _MEM__AST__NODE__RETURN__HPP_
#define _MEM__AST__NODE__RETURN__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {

// A return statement
//
// Syntax:
//    return <ValueNode>
//
// Ex:
//    return 1
class Return : public Node
{
   public:
   static const int kTYPE = MetaKind::RETURN;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Return ();

   // Destructor
   virtual
   ~Return ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER (MemorySize, int) {return sizeof(Return);}

   // ValueNode
   GETTER (ValueNode, Node*) {return _value_node;}
   SETTER (ValueNode, Node*) {_value_node = val;}


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

   Node* _value_node;
};


} } }

#endif
