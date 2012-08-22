#ifndef _MEM__AST__NODE__TUPLE__HPP_
#define _MEM__AST__NODE__TUPLE__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class Tuple: public Text
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Tuple();

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}
};


} } }

#endif
