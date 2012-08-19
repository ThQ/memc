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
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Number ();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   void
   isValid (NodeValidator* vld);
};

Number*
castToNumber (Node* n);

} } }


#endif
