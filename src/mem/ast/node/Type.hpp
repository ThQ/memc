#ifndef _MEM__AST__NODE__TYPE__HPP_
#define _MEM__AST__NODE__TYPE__HPP_


#include "mem/ast/node/NodeList.hpp"


namespace mem { namespace ast { namespace node {


class Type : public NodeList
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Type ();

   virtual
   GETTER(MemorySize, int) {return sizeof(Type);}
};


} } }

#endif
