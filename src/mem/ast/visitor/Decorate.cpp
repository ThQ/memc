#include "mem/ast/visitor/Decorate.hpp"


namespace mem { namespace ast { namespace visitor {


Decorate::Decorate (decorator::DecoratorMap decorators)
{
   _decorators = decorators;
   _name = "ast.Decorate";
}

bool
Decorate::visit (node::Node* node)
{
   if (node::isa<node::Func>(node))
   {
      node::Func* func = node::cast<node::Func>(node);
      if (func->DecoratorNode() != NULL)
      {
         node::Decorator* dec = func->DecoratorNode();
         if (dec != NULL && _decorators.find(dec->Value()) != _decorators.end())
         {
            _decorators[dec->Value()]->decorate(func->DecoratorNode());
         }
      }
      return false;
   }
   return true;
}


} } }
