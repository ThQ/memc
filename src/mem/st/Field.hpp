#ifndef _MEM__ST__FIELD__HPP_
#define _MEM__ST__FIELD__HPP_


#include "mem/st/Var.hpp"


namespace mem { namespace st {


class Field : public Var
{
   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   int _field_index;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   // -------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Field();

   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:
   GETTER(FieldIndex, int) {return _field_index;}
   SETTER(FieldIndex, int) {_field_index = val;}

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Ptr");return false;}
};

} }


#endif
