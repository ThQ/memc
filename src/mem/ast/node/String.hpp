#ifndef _MEM__AST__NODE__STRING__HPP_
#define _MEM__AST__NODE__STRING__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class String : public Text
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   String ();

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}

   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }

#endif
