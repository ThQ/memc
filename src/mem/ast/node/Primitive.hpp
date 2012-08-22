#ifndef _MEM__AST__NODE__PRIMITIVE__HPP_
#define _MEM__AST__NODE__PRIMITIVE__HPP_


#include "mem/ast/node/Type.hpp"


namespace mem { namespace ast { namespace node {


class Primitive : public Type
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Primitive ();

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}
};


} } }

#endif
