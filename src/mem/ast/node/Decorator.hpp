#ifndef _MEM__AST__NODE__DECORATOR__HPP_
#define _MEM__AST__NODE__DECORATOR__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class Decorator : public Text
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Decorator ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }

#endif
