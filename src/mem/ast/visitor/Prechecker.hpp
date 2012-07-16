#ifndef _MEM__AST__VISITOR__PRECHECKER__HPP_
#define _MEM__AST__VISITOR__PRECHECKER__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Text.hpp"
#include "mem/ast/visitor/Visitor.hpp"


namespace mem { namespace ast { namespace visitor {


/**
 * Checks basic signs of correctness before any other visitor is run.
 *
 * @FIXME It should be run before every visitor. At least in debug mode.
 */
class Prechecker : public Visitor
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Prechecker ();


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   /**
    * Visitor entry point.
    */
   virtual bool
   visit (node::Node* node);
};


} } }

#endif
