#ifndef _MEM__ST__VISITOR__DEP_BUILDER__HPP_
#define _MEM__ST__VISITOR__DEP_BUILDER__HPP_


#include "mem/st/Class.hpp"
#include "mem/st/Var.hpp"
#include "mem/dep/Tree.hpp"
#include "mem/st/visitor/Visitor.hpp"


namespace mem { namespace st { namespace visitor {


/**
 * This visitor builds the dependency tree.
 */
class DepBuilder : public Visitor
{
   public: dep::Tree _dep_tree;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   DepBuilder();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   bool
   visit (st::Symbol* symbol);

   void
   visitClass (st::Class* cls_sym);
};


} } }


#endif
