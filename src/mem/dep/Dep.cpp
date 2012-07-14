#include "mem/dep/Dep.hpp"


namespace mem { namespace dep {


Dep::Dep ()
{
   assert (_deps.size() == 0);
   _symbol = NULL;
}

Dep::~Dep ()
{
   for (std::map<st::Type*, Dep*>::iterator i = _deps.begin(); i!=_deps.end(); ++i)
   {
      delete i->second;
   }
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
