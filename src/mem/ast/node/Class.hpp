#ifndef _MEM__AST__NODE__CLASS__HPP_
#define _MEM__AST__NODE__CLASS__HPP_


#include "mem/ast/node/Text.hpp"
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
   // PUBLIC FUNCTIONS
   // -------------------------------------------------------------------------
   public:

   Text*
   gParentTypeNode ();
};


} } }

#endif
