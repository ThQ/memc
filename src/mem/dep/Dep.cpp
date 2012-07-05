#include "mem/dep/Dep.hpp"


namespace mem { namespace dep {


Dep::Dep ()
{
   assert (_deps.size() == 0);
   _symbol = NULL;
}

bool
Dep::addDependency (Dep* dep)
{
   assert (dep != NULL);
   assert (dep->gSymbol() != NULL);

   if (!dependsOn(dep->gSymbol()))
   {
      _deps[dep->gSymbol()] = dep;
      return true;
   }

   return false;
}

bool
Dep::dependsOn (st::Type* sym) const
{
   assert (sym != NULL);
   return _deps.find(sym) != _deps.end();
}


} }
