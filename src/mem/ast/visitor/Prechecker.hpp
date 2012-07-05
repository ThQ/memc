#ifndef _MEM__AST__VISITOR__PRECHECKER__HPP_
#define _MEM__AST__VISITOR__PRECHECKER__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Text.hpp"
#include "mem/ast/visitor/Visitor.hpp"


namespace mem { namespace ast { namespace visitor {


/**
 * @brief Checks basic sign of correctness before any other visitor is run.
 *
 * @FIXME It should be run before every visitor. At least in debug mode.
 */
class Prechecker : public Visitor
{
   /**
    * @brief Default constructor.
    */
   public: Prechecker ();

   /**
    * @brief Visitor entry point.
    */
   public: virtual bool visit (node::Node* node);
};


} } }

#endif
