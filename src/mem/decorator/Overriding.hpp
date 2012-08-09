#ifndef _MEM__DECORATOR__OVERRIDING__HPP_
#define _MEM__DECORATOR__OVERRIDING__HPP_


#include "mem/ast/node/Func.hpp"
#include "mem/decorator/FunctionDecorator.hpp"


namespace mem { namespace decorator {


class Overriding : public FunctionDecorator
{
   public:

   Overriding ();

   virtual bool
   decorate (ast::node::Node* n);
};


} }

#endif
