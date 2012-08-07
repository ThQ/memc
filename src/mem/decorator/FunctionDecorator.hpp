#ifndef _MEM__DECORATOR__FUNCTION_DECORATOR__HPP_
#define _MEM__DECORATOR__FUNCTION_DECORATOR__HPP_


#include "mem/decorator/Decorator.hpp"
#include "mem/st/Func.hpp"

namespace mem { namespace decorator {


class FunctionDecorator : public Decorator
{
   public:

   virtual bool
   decorate (ast::node::Node* node) {DEBUG_PRINT("func_deco.decorate\n");return false;}
};

} }

#endif
