#ifndef _MEM__ST__POINTER_TYPE__HPP
#define _MEM__ST__POINTER_TYPE__HPP


#include "mem/st/Type.hpp"


namespace mem { namespace st {


// A base class for pointer types.
//
// Pointer types are never created directly. Instead they are requested, and,
// if they don't exist yet, they are created. This is done in `st::util'.
class PointerType : public Type
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   PointerType ();

   // Destructor.
   virtual
   ~PointerType ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // BaseType
   GETTER(PointedType, Type*) {return _pointed_type;}
   SETTER(PointedType, Type*)
   {
      _pointed_type = val;
      if(val->isPointerType())
      {
         _ptr_level = static_cast<PointerType*>(val)->IndirectionLevel() + 1;
      }
   }

   // IndirectionLevel
   GETTER(IndirectionLevel, int) {return _ptr_level;}
   SETTER(IndirectionLevel, int) {_ptr_level = val;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Ptr");return false;}

   virtual bool
   canCastTo (Type* dest_ty) const;

   // Returns a child by its name.
   //
   // We have to override Symbol::getChild here because a pointer does not have
   // children of its own, instead it returns its base type's children. It acts
   // as a proxy. Pointers to pointer will simply chain.
   inline Symbol*
   getChild (std::string name) {return _pointed_type->getChild(name);}

   // Return the first non-pointer parent.
   Type*
   getNonPointerParent ();

   // True if this pointer type points to an array type.
   bool
   isPointerToArray () { return _pointed_type->isArrayType();}


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   // The type the pointer points to.
   //
   // This type is NOT taken into account when computing the byte size of the
   // pointer type since a pointer is always the same size, whatever the type
   // it points to.
   Type* _pointed_type;

   // The level of indirection between the pointer and the first non-pointer
   // type it points to.
   //
   // For example `char**' is a pointer to a pointer to char, which is a level
   // of indirection of two.
   // Pointer types cannot have a `_ptr_level' lower than 1.
   int _ptr_level;
};


} }

#endif
