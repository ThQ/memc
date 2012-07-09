#include "mem/st/visitor/DepBuilder.hpp"

namespace mem { namespace st { namespace visitor {


DepBuilder::DepBuilder ()
{
   _name = "st.DepBuilder";
}

bool
DepBuilder::visit (st::Symbol* sym)
{
   if (sym->isClassSymbol())
   {
      visitClass(static_cast<st::Class*>(sym));
   }
   return true;
}

void
DepBuilder::visitClass (st::Class* cls_sym)
{
   _dep_tree.addDependency(NULL, cls_sym);
}


} } }
