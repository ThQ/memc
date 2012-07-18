#ifndef _MEM__ST__ARG__HPP_
#define _MEM__ST__ARG__HPP_


#include "mem/st/Var.hpp"


namespace mem { namespace st {


class Arg : public Var
{
   // -------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   // -------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Arg();

   // -------------------------------------------------------------------------
   // PUBLIC METHODS
   // -------------------------------------------------------------------------
   public:

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Arg");return false;}
};

} }


#endif
