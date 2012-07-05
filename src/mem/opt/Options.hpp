#ifndef _MEM__OPT__OPTIONS__HPP_
#define _MEM__OPT__OPTIONS__HPP_


#include <map>
#include <string>
#include "mem/opt/Option.hpp"


namespace mem { namespace opt {


class Options
{
   public: std::string name;
   public: std::map<std::string, _Option*> _options;

   public:

   ~Options ();

   _Option*
   _getOptObject (std::string opt_name);

   BoolOption*
   _getBoolOptObject (std::string opt_name);

   StringOption*
   _getStrOptObject (std::string opt_name);

   void
   addOpt (_Option*);

   template <class T>
   EnumOption<T>*
   addEnumOpt (std::string name)
   {
      opt::EnumOption<T>* opt = new opt::EnumOption<T>();
      opt->_name = name;
      _options[name] = opt;
      return opt;
   }

   EnumOption<int>*
   addIntEnumOpt (std::string name)
   {
      EnumOption<int>* opt = addEnumOpt<int>(name);
      opt->_type = _Option::INT_ENUM;
      return opt;
   }

   void
   addBoolOpt (std::string name);

   void
   addStrOpt (std::string name);

   bool
   getBool (std::string name);

   std::string
   getStr (std::string name);

   int
   getInt (std::string opt_name)
   {
      _Option* opt = _getOptObject(opt_name);
      if (opt != NULL && opt->_type == _Option::INT_ENUM)
      {
         return static_cast<EnumOption<int>*>(opt)->_val;
      }
      return 0;
   }

   bool
   isSet (std::string name);

   bool
   set (std::string opt_name, std::string opt_value);
};

} }
#endif
