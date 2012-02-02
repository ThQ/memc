#ifndef _MEM__ST__SYMBOL_COLLECTION__HPP_
#define _MEM__ST__SYMBOL_COLLECTION__HPP_

namespace mem { namespace st {

template <class T>
class SymbolCollection
{
   public: unsigned int _child_count;
   public: T* _first_child;
   public: T* _last_child;

   //public: SymbolCollection ();
};


} }

#endif
