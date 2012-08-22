#ifndef _MEM__AST__NODE__ENUM__HPP_
#define _MEM__AST__NODE__ENUM__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


// An AST node for enumeration declarations
class Enum: public Text
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Enum ();


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
