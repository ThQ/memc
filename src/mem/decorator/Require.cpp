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
   DEBUG_REQUIRE (n->Parent() != NULL);
   DEBUG_REQUIRE (ast::node::isa<ast::node::Decorator>(n));
   DEBUG_REQUIRE (ast::node::isa<ast::node::Func>(n->Parent()));

   ast::node::Block* func_body = ast::node::cast<ast::node::Func>(n->Parent())->BodyNode();
   assert (func_body != NULL);

   ast::node::String* s = new ast::node::String();
   s->setValue("Requirement failed !");

   ast::node::Call* call = ast::util::createCall("c.stdio.puts", s);

   ast::node::Block* if_block = new ast::node::Block();
   if_block->addChild(call);

   ast::node::If* if_n = new ast::node::If();
   if_n->setConditionNode(n->getChild(0));
   if_n->setIfBlockNode(if_block);

   func_body->addChild(if_n);

   return true;
}

} }
