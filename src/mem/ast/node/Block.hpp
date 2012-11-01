#ifndef _MEM__AST__NODE__BLOCK__HPP_
#define _MEM__AST__NODE__BLOCK__HPP_


#include "mem/ast/node/NodeList.hpp"


namespace mem { namespace ast { namespace node {


class Block : public NodeList
{
   public:
   static const int kTYPE = MetaKind::BLOCK;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Block ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(MemorySize, int) {return sizeof(Block);}
};

} } }


#endif
