#ifndef _MEM__AST__NODE__ID__HPP_
#define _MEM__AST__NODE__ID__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class Id : public Text
{
   public:
   static const int kTYPE = MetaKind::ID;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Id ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return 0;}

   virtual
   GETTER(MemorySize, int) {return sizeof(Id);}


   //==========================================================================
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
