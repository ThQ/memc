#ifndef _MEM__ST__CLASS__HPP
#define _MEM__ST__CLASS__HPP


#include "mem/st/Field.hpp"
#include "mem/st/Type.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace st {


/**
 * A base class representing Class types.
 *
 * FIXME : Byte size does take into account ancestor's fields.
 */
class Class : public Type
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Class ();

   /**
    * Destructor.
    */
   virtual
   ~Class();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------

   /**
    * Returns the parent class in the type hierarchy.
    */
   GETTER(ParentClass, st::Class*) { return static_cast<st::Class*>(_parent);}
   SETTER(ParentClass, st::Class*) { _parent = val; }


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   bool
   addChild (st::Symbol* sym);

   /**
    * Return the number of fields in the class type, taking into account the
    * ancestor's fields.
    */
   int
   getAbsoluteFieldCount ();

   /**
    * Given a relative field index in a class type, return its absolute field
    * index.
    */
   int
   getFieldAbsoluteIndex (int field_relative_index);

   /**
    * Get a list of all the fields in the class type, including the ancestor's
    * fields.
    */
   std::vector<st::Field*>
   getOrderedFields();

   inline bool
   hasFields () {return _cur_field_index > 0;}

   /**
    * Checks wether a class depends on another (directly or indirectly).
    */
   bool
   isDependingOn (Class* cls);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   int _cur_field_index;
};


} }


#endif
