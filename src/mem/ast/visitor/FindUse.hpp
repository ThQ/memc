#ifndef _MEM__AST__VISITOR__FIND_USE__HPP_
#define _MEM__AST__VISITOR__FIND_USE__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Use.hpp"
#include "mem/ast/visitor/Visitor.hpp"


namespace mem { namespace ast { namespace visitor {


// Finds <use> statements.
//
// Once a file is successfully parsed and syntacticaly correct, this visitor
// looks for <use> statements in the AST and remembers them so as to inform
// the compiler.
//
// Without this visitor, only the entry point file would be parsed.
//
// This is a special visitor as it is run before any other and operates on a
// partial AST.
class FindUse : public Visitor
{
   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   FindUse();


   //==========================================================================
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   // Visitor entry point.
   virtual bool
   visit (node::Node* node);

   void
   visitFile (node::File* nodeFile);


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   std::vector<node::Use*> _uses; //! A vector of file names to be included
};


} } }

#endif
