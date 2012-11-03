#ifndef _MEM__AST__VISITOR__STATS__HPP_
#define _MEM__AST__VISITOR__STATS__HPP_


#include <iomanip>
#include <map>
#include <sstream>
#include "mem/ast/node/Node.hpp"
#include "mem/ast/visitor/Visitor.hpp"


namespace mem { namespace ast { namespace visitor {

struct KindStats
{
   int usages;
   int unit_memory_size;
   int total_memory_size;
};

// Generate statistics the AST
class Stats : public Visitor
{
   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   Stats ();


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   visit (node::Node* node);

   virtual bool
   tearDown ();


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   std::map<int, KindStats> _kind_usages;
};


} } }

#endif
