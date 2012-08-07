#ifndef _MEM__DECORATOR__REQUIRE__HPP_
#define _MEM__DECORATOR__REQUIRE__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/If.hpp"
#include "mem/ast/node/FinalId.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/String.hpp"
#include "mem/ast/util.hpp"
#include "mem/decorator/FunctionDecorator.hpp"


namespace mem { namespace decorator {

class Require : public FunctionDecorator
{
   public:

   Require();

   virtual bool
   decorate (ast::node::Node* n);
};

} }

#endif
