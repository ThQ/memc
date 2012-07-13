#ifndef _MEM__AST__NODE__USE__HPP_
#define _MEM__AST__NODE__USE__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class Use: public Text
{
   public: Use ();
   public: void isValid (NodeValidator* v);
};


} } }

#endif
