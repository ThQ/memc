#ifndef _MEM__ST__TUPLE_TYPE__HPP_
#define _MEM__ST__TUPLE_TYPE__HPP_


#include "mem/st/Type.hpp"


namespace mem { namespace st {

// A base class for all tuple types.
//
// A tuple is like a class type except its fields are unnamed.
// Tuple types must always be created in the `system' namespace.
class TupleType : public Type
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   TupleType();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(Subtypes, TypeVector) {return _subtypes;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   addChild (Symbol* s);

   // Add the types in @tys to the tuple subtypes.
   bool
   addTypes (TypeVector tys);

   // True if the types @tys are the subtypes of the tuple.
   bool
   hasTypes (TypeVector tys);


   //--------------------------------------------------------------------------
   // PROTECTED FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   // Recompute the type name.
   //
   // This is done every time a subtype is added.
   void
   _recomputeName ();


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   // The types of the components of the tuple.
   TypeVector _subtypes;
};

TupleType*
castToTupleType (Symbol* s);

} }


#endif
