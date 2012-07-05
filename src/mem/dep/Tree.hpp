#ifndef _MEM__DEP__TREE__HPP_
#define _MEM__DEP__TREE__HPP_


#include <map>
#include <set>
#include "mem/dep/Dep.hpp"


namespace mem { namespace dep {


/**
 * This class is used to represent a dependency tree.
 */
class Tree
{
   public: std::map<st::Type*, Dep*> _dep_list;
   public: Dep* _root;
   public: inline Dep* gRoot() const {return _root;}

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   Tree ();

   ~Tree ();
   public: bool addDependency (st::Type* src, st::Type* dest);
   public: bool hasSymbol (st::Type* sym);
};


} }


#endif
