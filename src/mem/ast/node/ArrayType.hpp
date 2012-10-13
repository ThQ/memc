#ifndef _MEM__AST__NODE__ARRAY_TYPE__HPP_
#define _MEM__AST__NODE__ARRAY_TYPE__HPP_


#include "mem/ast/node/Type.hpp"


namespace mem { namespace ast { namespace node {

// An array type declaration.
//
// Syntax:
//    [[Type], [Length]]
// Ex:
//    [int]
//    [int, 10]
class ArrayType : public Type
{
   public:
   static const int kTYPE = MetaKind::ARRAY;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   ArrayType ();

   // Destructor
   virtual
   ~ArrayType ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return 2;}

   GETTER(TypeNode, Node*) {return _type_node;}
   SETTER(TypeNode, Node*)
   {
      _type_node = val;
      if (val != NULL) val->setParent(this);
   }

   GETTER(LengthNode, Node*) {return _length_node;}
   SETTER(LengthNode, Node*)
   {
      _length_node = val;
      if (val != NULL) val->setParent(this);
   }

   virtual
   GETTER(MemorySize, int) {return sizeof(ArrayType);}


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
   Node* _length_node;
};

} } }

#endif
