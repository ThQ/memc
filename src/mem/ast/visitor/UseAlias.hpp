#ifndef _MEM__AST__VISITOR__USE_ALIAS__HPP_
#define _MEM__AST__VISITOR__USE_ALIAS__HPP_


#include "mem/ast/node/Use.hpp"
#include "mem/ast/visitor/Visitor.hpp"
#include "mem/fs/position/Composite.hpp"
#include "mem/st/Alias.hpp"
#include "mem/st/Util.hpp"


namespace mem { namespace ast { namespace visitor {


class UseAlias : public Visitor
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS/DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   UseAlias ();


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   visit (node::Node* node);
};


} } }


#endif
