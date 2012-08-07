#ifndef _MEM__DECORATOR__EXTERNAL__HPP_
#define _MEM__DECORATOR__EXTERNAL__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/If.hpp"
#include "mem/ast/node/FinalId.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/String.hpp"
#include "mem/ast/util.hpp"
#include "mem/decorator/FunctionDecorator.hpp"


namespace mem { namespace decorator {

class External : public FunctionDecorator
{
   public:

   External();

   virtual bool
   decorate (ast::node::Node* n);
};

} }

#endif
