#ifndef _MEM__AST__NODE__TUPLE_TYPE__HPP_
#define _MEM__AST__NODE__TUPLE_TYPE__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class TupleType : public Text
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   TupleType ();
};


} } }

#endif
