#ifndef _MEMC__OPT__OPTIONS__HPP_
#define _MEMC__OPT__OPTIONS__HPP_


#include <map>
#include <stack>
#include <ostream>
#include <string>
#include <string.h>
#include <vector>
#include "memc/opt/Option.hpp"


namespace memc { namespace opt {

typedef std::map<std::string, _Option*> OptionMap;

class Options
{
   public:

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   OptionMap _options;
   std::vector<std::string> _params;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   ~Options ();

   _Option*
   _getOptObject (std::string opt_name);


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   void
   addOpt (_Option*);

   EnumOption<int>*
   addIntEnumOpt (std::string long_name, std::string short_name, std::string desc)
   {
      EnumOption<int>* opt = new opt::EnumOption<int>();
      opt->setType(_Option::INT_ENUM);
      opt->setLongName(long_name);
      opt->setShortName(short_name);
      opt->setDescription(desc);

      addOpt(opt);

      return opt;
   }

   void
   addBoolOpt (std::string long_name, std::string short_name, std::string desc);

   void
   addStrOpt (std::string long_name, std::string short_name, std::string desc);

   void
   dump (std::ostream& out);

   inline std::string
   getArgument (size_t i) {return _params[i];}

   inline bool
   getBool (std::string name)
   {
      return getValue<bool, _Option::BOOL>(name, false);
   }

   int
   getEnumInt (std::string opt_name)
   {
      return getValue<int, _Option::INT_ENUM>(opt_name, 0);
   }

   int
   getInt (std::string opt_name)
   {
      return getValue<int, _Option::INT>(opt_name, 0);
   }

   inline std::string
   getStr (std::string name)
   {
      return getValue<std::string, _Option::STRING>(name, "");
   }

   template<class T, _Option::OptionType opt_ty> T
   getValue (std::string opt_name, T default_val)
   {
      _Option* opt = _getOptObject(opt_name);
      if (opt != NULL && opt->_type == opt_ty)
      {
         return static_cast< Option<T>* >(opt)->_val;
      }
      return default_val;
   }

   inline bool
   has (std::string name) {return _getOptObject(name)!=NULL;}

   inline bool
   hasArguments () {return _params.size() > 0;}

   bool
   isSet (std::string name);

   void
   parse (int argc, char** argv);

   bool
   set (std::string opt_name, std::string opt_value);
};

} }
#endif
