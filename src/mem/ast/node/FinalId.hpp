#ifndef _MEM__AST__NODE__FINAL_ID__HPP_
#define _MEM__AST__NODE__FINAL_ID__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class FinalId : public Text
{
   public:
   static const int kTYPE = MetaKind::FINAL_ID;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   FinalId ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return 0;}

   virtual
   GETTER(MemorySize, int) {return sizeof(FinalId);}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   copy () const;

   virtual void
   isValid (NodeValidator* v);
};

} } }

#endif
