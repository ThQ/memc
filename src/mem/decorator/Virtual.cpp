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
   DEBUG_REQUIRE (n->Parent() != NULL);
   DEBUG_REQUIRE (ast::node::isa<ast::node::Decorator>(n));
   DEBUG_REQUIRE (ast::node::isa<ast::node::Func>(n->Parent()));

   st::Func* func_sym = st::cast<st::Func>(n->Parent()->BoundSymbol());
   // FIXME
   if (!func_sym->IsOverriding())
   {
      st::Field* vfn_field = new st::Field();
      vfn_field->setName(func_sym->Name());
      vfn_field->setType(func_sym->Type()->FunctorType());
      vfn_field->setVirtualFunction(func_sym);
      func_sym->rename(func_sym->Name() + "!virtual");
      func_sym->Parent()->addChild(vfn_field);
   }
   else
   {
      func_sym->rename(func_sym->Name() + "!virtual");
   }

   func_sym->setIsVirtual(true);

   if (!func_sym->IsOverriding())
   {
   }
   else
   {
      DEBUG_PRINTF("Virtual function %s is overriding\n", func_sym->gQualifiedNameCstr());
   }


   return true;
}

} }
