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

   /**
    * Default constructor.
    */
   Constant ();

   public:
   GETTER(Type, st::Type*) {return _type;}
   SETTER(Type, st::Type*) {_type = val;}

   protected:
   st::Type* _type;
};

} }


#endif
