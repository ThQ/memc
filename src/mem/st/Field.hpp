#ifndef _MEM__ST__FIELD__HPP_
#define _MEM__ST__FIELD__HPP_


#include "mem/st/Var.hpp"


namespace mem { namespace st {


class Field : public Var
{
   // -------------------------------------------------------------------------
   // FIELDS
   // -------------------------------------------------------------------------
   public:

   int _field_index;

   // -------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   // -------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Field();

   // -------------------------------------------------------------------------
   // PUBLIC METHODS
   // -------------------------------------------------------------------------
   public:

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Ptr");return false;}
};

} }


#endif
