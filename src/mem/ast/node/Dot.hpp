#ifndef _MEM__AST__NODE__DOT__HPP_
#define _MEM__AST__NODE__DOT__HPP_

#include "mem/ast/node/BinaryOp.hpp"


namespace mem { namespace ast { namespace node {

// A class to represent the dot operator
//
// Syntax:
//    [Left].[Right]
//
// Ex:
//    my_namespace.my_class
class Dot: public BinaryOp
{
   public:
   static const int kTYPE = Kind::DOT;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Dot();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER (MemorySize, int) {return sizeof(Dot);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }

#endif
