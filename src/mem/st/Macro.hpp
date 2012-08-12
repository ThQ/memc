#ifndef _MEM__ST__MACRO__HPP_
#define _MEM__ST__MACRO__HPP_


#include "mem/st/Func.hpp"


namespace mem { namespace st {

class Macro : public Func
{
   protected:
   void* _macro_expander;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Macro ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------

   GETTER(MacroExpander, void*) {return _macro_expander;}
   SETTER(MacroExpander, void*) {_macro_expander = val;}
};

} }


#endif
