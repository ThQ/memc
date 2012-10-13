#ifndef _MEM__AST__NODE__NUMBER__HPP_
#define _MEM__AST__NODE__NUMBER__HPP_


#include <string>
#include <sstream>
#include "mem/ast/node/Node.hpp"
#include "mem/st/IntConstant.hpp"


namespace mem { namespace ast { namespace node {


// A class to represent literal numbers.
class Number : public Node
{
   public:
   static const int kTYPE = MetaKind::NUMBER;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Number ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return 0;}

   virtual
   GETTER(MemorySize, int) {return sizeof(Number);}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   void
   isValid (NodeValidator* vld);
};

} } }


#endif
