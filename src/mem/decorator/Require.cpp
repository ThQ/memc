#include "mem/decorator/Require.hpp"

namespace mem { namespace decorator {

Require::Require ()
{
   _name = "require";
}

bool
Require::decorate (ast::node::Node* n)
{
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->isDecoratorNode());
   DEBUG_REQUIRE (n->Parent()->isFuncNode());

   ast::node::Node* func_body = static_cast<ast::node::Func*>(n->Parent())->BodyNode();
   assert (func_body != NULL);

   ast::node::String* s = new ast::node::String();
   s->sValue("Requirement failed !");

   ast::node::Call* call = ast::util::createCall("c.stdio.puts", s);

   ast::node::Block* if_block = new ast::node::Block();
   if_block->pushChild(call);

   ast::node::If* nif = new ast::node::If();
   nif->pushChildren(n->getChild(0), if_block);

   func_body->insertChild(nif);
   n->unlinkChildren();

   return true;
}

} }
