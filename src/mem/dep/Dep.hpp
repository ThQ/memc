#ifndef _MEM__DEP__DEP__HPP_
#define _MEM__DEP__DEP__HPP_


#include <map>
#include "mem/st/Type.hpp"


namespace mem { namespace dep {


/**
 * This is a node in the dependency tree.
 */
class Dep
{
   public: std::map<st::Type*, Dep*> _deps;


   // PROPERTY : Symbol
   public: st::Type* _symbol;
   public: inline void sSymbol (st::Type* sym) {_symbol = sym;}
   public: inline st::Type* gSymbol () const {return _symbol;}


   public:

   Dep();

   bool
   addDependency (Dep* dep);

   bool
   dependsOn (st::Type* sym) const;
};


} }


#endif
