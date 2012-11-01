#ifndef _MEM__AST__NODE__TUPLE__HPP_
#define _MEM__AST__NODE__TUPLE__HPP_


#include "mem/ast/node/NodeList.hpp"


namespace mem { namespace ast { namespace node {


class Tuple: public NodeList
{
   public:
   static const int kTYPE = MetaKind::TUPLE;


   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Tuple ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER (MemorySize, int) {return sizeof(Tuple);}
};


} } }

#endif
