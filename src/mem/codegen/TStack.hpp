#ifndef _MEM__CODEGEN__STACK__HPP_
#define _MEM__CODEGEN__STACK__HPP_


#include <deque>
#include <map>
#include <stdio.h>
#include <string>


namespace mem { namespace codegen {


template <class K, class V>
class TStack
{
   public: std::deque<std::map<K, V> > _vars;

   public: V get (K name)
   {
      assert (_vars.size() > 0);

      size_t i = _vars.size() - 1;
      while (true)
      {
         if (_vars[i].find(name) != _vars[i].end())
         {
            return _vars[i][name];
         }
         if (i == 0) break;
         --i;
      }
      V res;
      return res;
   }

   public: void pop ()
   {
      _vars.pop_back();
   }

   public: void push ()
   {
      std::map<K, V> p;
      _vars.push_back(p);
   };

   public: void set (K name, V val)
   {
      assert (_vars.size() > 0);
      _vars.back()[name] = val;
   }

   public: void setGlobal (K name, V val)
   {
      assert (_vars.size() > 0);
      _vars.front()[name] = val;
   }

   public: inline size_t size()
   {
      return _vars.size();
   }

};


} }


#endif
