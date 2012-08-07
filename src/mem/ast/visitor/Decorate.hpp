#ifndef _MEM__AST__VISITOR__DECORATE__HPP_
#define _MEM__AST__VISITOR__DECORATE__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Text.hpp"
#include "mem/ast/visitor/BlockTypesChecker.hpp"
#include "mem/decorator/Decorator.hpp"


namespace mem { namespace ast { namespace visitor {


// Visit decorators and run them
class Decorate : public BlockTypesChecker
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Decorate (decorator::DecoratorMap decorators);


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   // Visitor entry point.
   virtual bool
   visit (node::Node* node);

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   decorator::DecoratorMap _decorators;
};


} } }

#endif
