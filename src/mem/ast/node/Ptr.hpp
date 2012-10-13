#ifndef _MEM__AST__NODE__PTR__HPP_
#define _MEM__AST__NODE__PTR__HPP_


#include "mem/ast/node/Type.hpp"


namespace mem { namespace ast { namespace node {

// A class to represent pointer types
//
// Syntax:
//    <Type>*
//
// Ex:
//    int*
class Ptr: public Type
{
   public:
   static const int kTYPE = MetaKind::POINTER_TYPE;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Ptr ();

   // Destructor
   virtual
   ~Ptr ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // MemorySize
   virtual
   GETTER(MemorySize, int) {return sizeof(Ptr);}

   // TypeNode
   GETTER(TypeNode, node::Node*) {return _type_node;}
   SETTER(TypeNode, node::Node*)
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

   node::Node* _type_node;
};

} } }

#endif
