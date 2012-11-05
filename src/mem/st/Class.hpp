#ifndef _MEM__ST__CLASS__HPP
#define _MEM__ST__CLASS__HPP


#include "mem/st/Field.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/Type.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace st {


// A base class representing Class types.
//
// FIXME : Byte size does take into account ancestor's fields.
class Class : public Type
{
   public:
   static const int kTYPE = MetaKind::CLASS_TYPE;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Class ();

   // Destructor
   virtual
   ~Class();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------

   virtual GETTER(ByteSize, int)
   {
      return ParentClass() != NULL && st::isa<Class>(ParentClass()) ? ParentClass()->ByteSize() + _byte_size : _byte_size;
   }

   GETTER(DefaultCtor, Func*) { return _default_ctor;}
   SETTER(DefaultCtor, Func*) { _default_ctor = val;}

   // The parent class in the type hierarchy.
   GETTER(ParentClass, st::Class*) { return _parent_type != NULL ? st::cast<st::Class>(_parent_type) : NULL;}
   SETTER(ParentClass, st::Class*) { _parent_type = val;}

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   bool
   addChild (st::Symbol* sym);

   // Return the number of fields in the class type, taking into account the
   // ancestor's fields.
   int
   getAbsoluteFieldCount ();

   FieldVector
   getAllFields ();

   // Given a relative field index in a class type, return its absolute field
   // index.
   int
   getFieldAbsoluteIndex (int field_relative_index);

   FunctionVector
   getFunctionsLike (std::string name, FunctionType* func_ty);

   // Get a list of all the fields in the class type, including the ancestor's
   // fields.
   std::vector<st::Field*>
   getOrderedFields();

   // True if the class type has fields of its own.
   //
   // FIXME: This should take into account the ancestor's fields.
   inline bool
   hasFields () {return _cur_field_index > 0;}

   // Checks wether a class depends on another (directly or indirectly).
   bool
   isDependingOn (Class* cls);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   int _cur_field_index;
   Func* _default_ctor;
};

} }


#endif
