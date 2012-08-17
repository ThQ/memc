#include "mem/st/visitor/Visitor.hpp"

namespace mem { namespace st { namespace visitor {

Visitor::~Visitor()
{

}

void
Visitor::visitPreorder (st::Symbol* sym)
{
   if (visit(sym))
   {
      st::Symbol::SymbolCollectionIterator i;
      for (i=sym->Children().begin(); i != sym->Children().end(); ++i)
      {
         this->visitPreorder(i->second);
      }
   }
}

} } }
