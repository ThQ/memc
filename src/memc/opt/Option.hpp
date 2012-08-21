#ifndef _MEMC__OPT__OPTION__HPP_
#define _MEMC__OPT__OPTION__HPP_


#include <assert.h>
#include <map>
#include <string>
#include "mem/ss.hpp"


namespace memc { namespace opt {


class _Option
{
   public: typedef enum {NONE, STRING, BOOL, INT, INT_ENUM} OptionType;
   public: std::string _long_name;
   public: std::string _short_name;
   public: std::string _desc;
   public: bool _is_set;
   public: OptionType _type;

   public: _Option();
   public: virtual ~_Option() {};

   GETTER(Description, std::string) {return _desc;}
   SETTER(Description, std::string) {_desc = val;}

   GETTER(LongName, std::string) {return _long_name;}
   SETTER(LongName, std::string) {_long_name = val;}

   GETTER(Type, _Option::OptionType) {return _type;}
   SETTER(Type, _Option::OptionType) {_type = val;}

   GETTER(ShortName, std::string) {return _short_name;}
   SETTER(ShortName, std::string) {_short_name = val;}
};


template <class T>
class Option : public _Option
{
   public: T _val;
};


template <>
class Option <std::string> : public _Option
{
   public: std::string _val;
   public: Option() {_type = STRING;}
   public: Option (std::string long_name, std::string short_name, std::string description)
   {

   }
   public: bool setVal (std::string val, bool is_set=true)
   {
      _val = val;
      _is_set = is_set;
      return true;
   }
};

template <>
class Option <bool> : public _Option
{
   public: bool _val;
   public: Option() {_type = BOOL;_val=false;}
};

template <class T>
class EnumOption : public _Option
{
   public: T _val;
   public: std::map<std::string, T> _enum;

   public: EnumOption () {_type = NONE;}

   public: EnumOption<T>* bind (std::string name, T val)
   {
      _enum[name] = val;
      return this;
   }

   public: virtual bool setVal (std::string str_val)
   {
      if (_enum.find(str_val) != _enum.end())
      {
         _val = _enum[str_val];
         _is_set = true;
         return true;
      }
      return false;
   }
};


typedef Option<std::string> StringOption;
typedef Option<bool> BoolOption;


} }
#endif
