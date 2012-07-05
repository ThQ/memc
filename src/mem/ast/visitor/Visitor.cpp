#include "mem/ast/visitor/Visitor.hpp"

namespace mem { namespace ast { namespace visitor {


Visitor::~Visitor ()
{
}

void
Visitor::setup (st::SymbolTable* symbols, log::Logger* logger)
{
   assert(symbols != NULL);
   assert(logger != NULL);

   _core_types = &symbols->gCoreTypes();
   _symbols = symbols;
   _logger = logger;
}

void
Visitor::tearDown ()
{
}

bool
Visitor::visit (node::Node* node)
{
   return false;
}

void
Visitor::visit_preorder (node::Node* node)
{
   if (visit(node))
   {
      node::Node* child_node = node->_first_child;
      while (child_node != NULL)
      {
         visit_preorder(child_node);
         child_node = child_node->_next;
      }
   }
}


} } }
