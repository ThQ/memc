#ifndef _MEM__ST__CONSTANT__HPP_
#define _MEM__ST__CONSTANT__HPP_


#include "mem/st/Type.hpp"
#include "mem/st/Symbol.hpp"


namespace mem { namespace st {


class Constant : public Type
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Constant ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // Type
   GETTER(Type, st::Type*) {return _type;}
   SETTER(Type, st::Type*) {_type = val;}


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   st::Type* _type;
};

} }


#endif
