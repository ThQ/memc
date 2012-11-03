#include "mem/ast/visitor/Decorate.hpp"


namespace mem { namespace ast { namespace visitor {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Decorate::Decorate (decorator::DecoratorMap decorators)
{
   _decorators = decorators;
   _name = "ast.Decorate";
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
Decorate::visit (node::Node* node)
{
   if (node::isa<node::Func>(node))
   {
      node::Func* nodeFunc = node::cast<node::Func>(node);
      if (nodeFunc->DecoratorNode() != NULL)
      {
         node::Decorator* dec = nodeFunc->DecoratorNode();
         if (dec != NULL && _decorators.find(dec->Value()) != _decorators.end())
         {
            _decorators[dec->Value()]->decorate(nodeFunc->DecoratorNode());
         }
      }
      return false;
   }
   return true;
}


} } }
