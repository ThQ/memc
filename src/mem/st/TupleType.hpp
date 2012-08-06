#ifndef _MEM__ST__TUPLE_TYPE__HPP_
#define _MEM__ST__TUPLE_TYPE__HPP_


#include "mem/st/Type.hpp"


namespace mem { namespace st {


class TupleType : public Type
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
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

   bool
   addTypes (TypeVector tys);

   bool
   hasTypes (TypeVector tys);


   //--------------------------------------------------------------------------
   // PROTECTED FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   void
   _recomputeName ();

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   TypeVector _subtypes;
};

} }


#endif
