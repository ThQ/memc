#ifndef _MEM__AST__NODE__NEW__HPP_
#define _MEM__AST__NODE__NEW__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {

// A dynamic memory allocation
//
// Syntax:
//    new <TypeNode>
//
// Ex:
//    new [int, 10]
class New : public Node
{
   public:
   static const int kTYPE = MetaKind::NEW;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   New ();

   // Destructor
   virtual
   ~New ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return 1;}

   virtual
   GETTER(MemorySize, int) {return sizeof(New);}

   // TypeNode
   GETTER(TypeNode, Node*) {return _type_node;}
   SETTER(TypeNode, Node*)
   {
      _type_node = val;
      if (val != NULL) val->setParent(this);
   }


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

   Node* _type_node;
};


} } }

#endif
