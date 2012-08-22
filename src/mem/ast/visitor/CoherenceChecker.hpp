#ifndef _MEM__AST__VISITOR__COHERENCE_CHECKER__HPP_
#define _MEM__AST__VISITOR__COHERENCE_CHECKER__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/visitor/TopTypesChecker.hpp"


namespace mem { namespace ast { namespace visitor {


class CoherenceChecker : public TopTypesChecker
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   CoherenceChecker();


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   // Visitor entry point.
   virtual bool
   visit (node::Node* node);
};


} } }

#endif
