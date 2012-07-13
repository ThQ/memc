#ifndef _MEM__ST__PRIMITIVE__HPP
#define _MEM__ST__PRIMITIVE__HPP


#include "mem/st/Type.hpp"


namespace mem { namespace st {


class Primitive : public Type
{
   public: Primitive ();

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Primitive");return false;}
};


} }

#endif
