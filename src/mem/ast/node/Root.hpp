#ifndef _MEM__AST__NODE__ROOT__HPP_
#define _MEM__AST__NODE__ROOT__HPP_


#include "mem/ast/node/NodeList.hpp"


namespace mem { namespace ast { namespace node {


class Root : public NodeList
{
   public:
   static const int kTYPE = MetaKind::ROOT;


   //==========================================================================
   // CONSTRUCTORS / DESTRUTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Root ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER (MemorySize, int) {return sizeof(Root);}
};


} } }

#endif
