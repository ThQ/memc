#ifndef _MEM__AST__VISITOR__CHECK_VALIDITY__HPP_
#define _MEM__AST__VISITOR__CHECK_VALIDITY__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Text.hpp"
#include "mem/ast/visitor/Visitor.hpp"


namespace mem { namespace ast { namespace visitor {

/**
 * Checks the validity of each node in the final AST (before optimisation).
 *
 * Once we know the AST is expected to be valid we run this final test so as to
 * ensure its validity is perfect. In theory this should not raise any error.
 * In practice, if it raises an error :
 * 1/ The isValid function of the supposed invalid node is bogus (false positive)
 * 2/ There is a real bug that needs to be fixed (and it will be hard)
 */
class CheckValidity : public Visitor
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   CheckValidity();


   //--------------------------------------------------------------------------
   // PUBLIC METHODS
   //--------------------------------------------------------------------------
   public:

   /**
    * Visitor entry point.
    */
   virtual bool visit (node::Node* node);
};


} } }

#endif
