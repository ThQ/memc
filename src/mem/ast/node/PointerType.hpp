#ifndef _MEM__AST__NODE__POINTER_TYPE__HPP_
#define _MEM__AST__NODE__POINTER_TYPE__HPP_


#include "mem/ast/node/Type.hpp"


namespace mem { namespace ast { namespace node {

// A class to represent pointer types
//
// Syntax:
//    <Type>*
//
// Ex:
//    int*
class PointerType: public Id
{
   public:
   static const int kTYPE = MetaKind::POINTER_TYPE;


   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   PointerType ();

   // Destructor
   virtual
   ~PointerType ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // MemorySize
   virtual
   GETTER(MemorySize, int) {return sizeof(PointerType);}

   // TypeNode
   GETTER(TypeNode, node::Node*) {return _nodeType;}
   SETTER(TypeNode, node::Node*)
   {
      _nodeType = val;
      if (val != NULL) val->setParent(this);
   }


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
   protected:

   node::Node* _nodeType;
};

} } }

#endif
