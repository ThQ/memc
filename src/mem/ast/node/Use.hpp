#ifndef _MEM__AST__NODE__USE__HPP_
#define _MEM__AST__NODE__USE__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class Use: public Text
{
   public:
   static const int kTYPE = MetaKind::USE;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Use ();

   virtual
   GETTER (MemorySize, int) {return sizeof(Use);}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   void
   isValid (NodeValidator* v);
};


} } }


#endif
