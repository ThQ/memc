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

   //FIXME We MUST check if there is already a field by that name

   st::Field* field = new st::Field();
   field->setName(func_sym->Name());
   field->setType(func_sym->Type()->FunctorType());
   field->setVirtualFunction(func_sym);

   func_sym->setName(func_sym->Name() + "!virtual");
   func_sym->Parent()->addChild(field);

   return true;
}

} }
