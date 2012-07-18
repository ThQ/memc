#ifndef _MEM__AST__NODE__FINAL_ID__HPP_
#define _MEM__AST__NODE__FINAL_ID__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class FinalId : public Text
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   FinalId ();


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }

#endif
