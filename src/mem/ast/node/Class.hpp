#ifndef _MEM__AST__NODE__CLASS__HPP_
#define _MEM__AST__NODE__CLASS__HPP_


#include "mem/ast/node/Type.hpp"


namespace mem { namespace ast { namespace node {


class Class : public Type
{
   // -------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   // -------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Class ();


   // -------------------------------------------------------------------------
   // FUNCTIONS
   // -------------------------------------------------------------------------
   public:

   Node*
   gParentTypeNode ();

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}


};


} } }

#endif
