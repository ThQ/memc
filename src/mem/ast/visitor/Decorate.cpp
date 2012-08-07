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
   if (node->isFuncNode())
   {
      node::Func* func = static_cast<node::Func*>(node);
      if (func->DecoratorNode() != NULL)
      {
         node::Decorator* dec = func->DecoratorNode();
         DEBUG_PRINTF("Shoud decorate ! (%s) %d decos\n", dec->gValueCstr(), _decorators.size());
         if (dec != NULL && _decorators.find(dec->gValue()) != _decorators.end())
         {
            DEBUG_PRINT("Will decorate !\n");
            _decorators[dec->gValue()]->decorate(func->DecoratorNode());
         }
      }
      return false;
   }
   return true;
}


} } }
