#ifndef _MEM__CODEGEN__STACK__HPP_
#define _MEM__CODEGEN__STACK__HPP_


#include <deque>
#include <map>
#include <string>


namespace mem { namespace codegen {


template <class T>
class TStack
{
   private: std::deque<std::map<std::string, T> > _vars;

   public: T get (std::string name)
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
      T res;
      return res;
   }

   public: void pop ()
   {
      _vars.pop_back();
   }

   public: void push ()
   {
      std::map<std::string, T> p;
      _vars.push_back(p);
   };

   public: void set (std::string name, T val)
   {
      assert (_vars.size() > 0);
      _vars.back()[name] = val;
   }

};


} }


#endif
