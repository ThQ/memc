#include "mem/st/visitor/Visitor.hpp"

namespace mem { namespace st { namespace visitor {

void
Visitor::visitPreorder (st::Symbol* sym)
{
   if (visit(sym))
   {
      st::Symbol* cur_sym = NULL;
      st::Symbol::SymbolCollectionIterator i;
      for (i=sym->Children().begin(); i != sym->Children().end(); ++i)
      {
         this->visitPreorder(i->second);
      }
   }
}

} } }
