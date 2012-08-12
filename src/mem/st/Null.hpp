#ifndef _MEM__ST__NULL__HPP_
#define _MEM__ST__NULL__HPP_


#include "mem/st/Constant.hpp"


namespace mem { namespace st {

// A base class to represent the NULL constant.
//
// It is a separated class to make equality tests easier : we don't have to
// have the symbol table to compare.
class Null : public Constant
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Null();
};


} }


#endif
