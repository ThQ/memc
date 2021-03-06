#ifndef _MEM__AST__NODE__STRING__HPP_
#define _MEM__AST__NODE__STRING__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class String : public Text
{
   public:
   static const int kTYPE = MetaKind::STRING;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   String ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return 0;}

   virtual
   GETTER(MemorySize, int) {return sizeof(String);}


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }

#endif
