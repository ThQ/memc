#ifndef _MEM__DECORATOR__VIRTUAL__HPP_
#define _MEM__DECORATOR__VIRTUAL__HPP_


#include "mem/ast/node/Func.hpp"
#include "mem/decorator/FunctionDecorator.hpp"


namespace mem { namespace decorator {


class Virtual : public FunctionDecorator
{
   public:

   Virtual ();

   virtual bool
   decorate (ast::node::Node* n);
};


} }

#endif
