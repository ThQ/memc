#ifndef _MEM__ST__FIELD__HPP_
#define _MEM__ST__FIELD__HPP_


#include "mem/st/Func.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace st {


class Field : public Var
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   // -------------------------------------------------------------------------
   public:

   // Default constructor.
   Field();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(FieldIndex, int) {return _field_index;}
   SETTER(FieldIndex, int) {_field_index = val;}

   GETTER(VirtualFunction, Func*) {return _virtual_function;}
   SETTER(VirtualFunction, Func*) {_virtual_function = val;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Ptr");return false;}


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   int _field_index;
   Func* _virtual_function;
};

typedef std::vector<Field*> FieldVector;

} }


#endif
