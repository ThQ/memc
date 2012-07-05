#include "mem/opt/Options.hpp"

namespace mem { namespace opt {


Options::~Options ()
{
   for (std::map<std::string, _Option*>::iterator i= _options.begin(); i!= _options.end(); ++i)
   {
      delete i->second;
   }
}

_Option*
Options::_getOptObject (std::string opt_name)
{
   if (_options.find(opt_name) != _options.end())
   {
      return _options[opt_name];
   }
   return NULL;
}

BoolOption*
Options::_getBoolOptObject (std::string opt_name)
{
   _Option* opt = _getOptObject(opt_name);
   if (opt != NULL && opt->_type == _Option::BOOL)
   {
      return static_cast<BoolOption*>(opt);
   }
   return NULL;
}

StringOption*
Options::_getStrOptObject (std::string opt_name)
{
   _Option* opt = _getOptObject(opt_name);
   if (opt != NULL && opt->_type == _Option::STRING)
   {
      return static_cast<StringOption*>(opt);
   }
   return NULL;
}

bool
Options::getBool (std::string opt_name)
{
   BoolOption* opt = _getBoolOptObject(opt_name);
   if (opt != NULL) return opt->_val;
   return false;
}

std::string
Options::getStr (std::string opt_name)
{
   StringOption* opt = _getStrOptObject(opt_name);

   if (opt != NULL)
   {
      return opt->_val;
   }
   return "";
}

bool
Options::isSet (std::string opt_name)
{
   if (_options.find(opt_name) != _options.end())
   {
      return _options.find(opt_name)->second->_is_set;
   }
   return false;
}

void
Options::addOpt (_Option* opt)
{
   _options[opt->_name] = opt;
}

void
Options::addBoolOpt (std::string name)
{
   BoolOption* opt = new BoolOption();
   opt->_type = _Option::BOOL;
   opt->_name = name;

   addOpt(opt);
}

void
Options::addStrOpt (std::string name)
{
   StringOption* opt = new StringOption();
   opt->_type = _Option::STRING;
   opt->_name = name;

   addOpt(opt);
}

bool
Options::set(std::string opt_name, std::string opt_value)
{
   _Option* opt = _getOptObject(opt_name);
   if (opt != NULL)
   {
      if (opt->_type == _Option::STRING)
      {
         static_cast<StringOption*>(opt)->_val = opt_value;
         opt->_is_set = true;
         return true;
      }
      else if (opt->_type == _Option::INT_ENUM)
      {
         static_cast<EnumOption<int>*>(opt)->setVal(opt_value);
         opt->_is_set = true;
         return true;
      }
   }
   assert (false && "Options does not exist.");
   return false;
}


} }
