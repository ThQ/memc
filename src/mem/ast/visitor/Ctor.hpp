#ifndef _MEM__AST__VISITOR__CTOR__HPP_
#define _MEM__AST__VISITOR__CTOR__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/visitor/TopTypesChecker.hpp"


namespace mem { namespace ast { namespace visitor {


class Ctor : public TopTypesChecker
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Ctor();


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   void
   initializeField (st::Field* field, node::Block* ctor);

   // Visitor entry point.
   virtual bool
   visit (node::Node* node);

   void
   visitClass (class node::Class* n);
};


} } }

#endif
