#include "mem/decorator/External.hpp"

namespace mem { namespace decorator {

External::External ()
{
   _name = "external";
}

bool
External::decorate (ast::node::Node* n)
{
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->Parent() != NULL);
   DEBUG_REQUIRE (ast::node::isa<ast::node::Decorator>(n));
   DEBUG_REQUIRE (ast::node::isa<ast::node::Func>(n));

   st::Func* func_sym = static_cast<st::Func*>(n->Parent()->BoundSymbol());
   func_sym->setIsExternal(true);

   return true;
}

} }
