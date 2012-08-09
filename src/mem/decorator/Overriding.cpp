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
   DEBUG_REQUIRE (n->isDecoratorNode());
   DEBUG_REQUIRE (n->Parent()->isFuncNode());

   st::Func* func_sym = static_cast<st::Func*>(n->Parent()->BoundSymbol());
   func_sym->setIsOverriding(true);

   return true;
}

} }
