#include "mem/decorator/Overriding.hpp"

namespace mem { namespace decorator {

Overriding::Overriding ()
{
   _name = "overriding";
}

bool
Overriding::decorate (ast::node::Node* n)
{
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (ast::node::isa<ast::node::Decorator>(n));
   DEBUG_REQUIRE (ast::node::isa<ast::node::Func>(n->Parent()));

   //FIXME Do something here
   st::Func* func_sym = static_cast<st::Func*>(n->Parent()->BoundSymbol());
   if (!func_sym->IsOverriding())
   {
      DEBUG_PRINT("Function is decorated `@overriding' but does not override a function");
   }
   //func_sym->setIsOverriding(true);

   return true;
}

} }
