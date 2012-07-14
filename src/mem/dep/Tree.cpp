#include "mem/dep/Tree.hpp"


namespace mem { namespace dep {


Tree::Tree ()
{
   _root = new Dep();
}

Tree::~Tree ()
{
   for (std::map<st::Type*, Dep*>::iterator i=_dep_list.begin(); i != _dep_list.end(); ++i)
   {
      delete i->second;
   }
   delete _root;
}

bool
Tree::addDependency (st::Type* src, st::Type* dest)
{
   bool has_src = hasSymbol(src);
   bool has_dest = hasSymbol(dest);

   Dep* src_dep = NULL;

   if (src == NULL)
   {
      src_dep = _root;
   }
   else if (!has_src)
   {
      src_dep = new Dep();
      src_dep->sSymbol(src);
      _dep_list[src] = src_dep;
   }
   else
   {
      src_dep = _dep_list[src];
   }

   Dep* dest_dep = NULL;
   if (!has_dest)
   {
      dest_dep = new Dep();
      dest_dep->sSymbol(dest);
      _dep_list[dest] = dest_dep;
   }
   else
   {
      dest_dep = _dep_list[dest];
   }

   return src_dep->addDependency(dest_dep);
}

bool
Tree::hasSymbol (st::Type* sym)
{
   if (sym != NULL)
   {
      return _dep_list.find(sym) != _dep_list.end();
   }
   return false;
}

} }
