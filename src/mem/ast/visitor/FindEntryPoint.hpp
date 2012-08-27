#ifndef _MEM__AST__VISITOR__FIND_ENTRY_POINT__HPP_
#define _MEM__AST__VISITOR__FIND_ENTRY_POINT__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/visitor/Visitor.hpp"


namespace mem { namespace ast { namespace visitor {


/**
 * Visits the AST in order to find an entry point (a function declaration for
 * main, ie :
 * >   main () -> int
 */
class FindEntryPoint : public Visitor
{
   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   st::Symbol* _entry_point;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   FindEntryPoint();


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   tearDown ();

   virtual bool
   visit (node::Node* node);
};


} } }

#endif
