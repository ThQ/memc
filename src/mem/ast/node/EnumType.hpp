#ifndef _MEM__AST__NODE__ENUM__HPP_
#define _MEM__AST__NODE__ENUM__HPP_


#include "mem/ast/node/Class.hpp"


namespace mem { namespace ast { namespace node {


// An AST node for enumeration declarations
class EnumType : public Class
{
   public:
   static const int kTYPE = Kind::ENUM;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   EnumType ();

   virtual
   GETTER(MemorySize, int) {return sizeof(EnumType);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};

} } }

#endif
