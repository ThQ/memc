#include "mem/decorator/Virtual.hpp"

namespace mem { namespace decorator {

Virtual::Virtual ()
{
   _name = "virtual";
}

bool
Virtual::decorate (ast::node::Node* n)
{
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->isDecoratorNode());
   DEBUG_REQUIRE (n->Parent()->isFuncNode());

   st::Func* func_sym = static_cast<st::Func*>(n->Parent()->BoundSymbol());
   func_sym->setIsVirtual(true);

   return true;
}

} }
