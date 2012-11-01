#ifndef _MEM__AST__NODE__TEXT_NODE__HPP_
#define _MEM__AST__NODE__TEXT_NODE__HPP_


#include <string.h>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class Text: public Node
{
   public:
   static const int kTYPE = MetaKind::TEXT;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Text ();
};


} } }


#endif
