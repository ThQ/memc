#ifndef _MEM__ST__ARG__HPP_
#define _MEM__ST__ARG__HPP_


#include "mem/st/Var.hpp"


namespace mem { namespace st {


// A symbol to represent function arguments.
//
// We do not use an st::Var because we need to make the distinction sometimes
// (in codegen::Llvm for example).
class Arg : public Var
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Arg();

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Arg");return false;}
};

} }


#endif
