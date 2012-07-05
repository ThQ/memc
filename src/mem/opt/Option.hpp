#ifndef _MEM__OPT__OPTION__HPP_
#define _MEM__OPT__OPTION__HPP_


#include <assert.h>
#include <map>
#include <string>


namespace mem { namespace opt {


class _Option
{
   public: typedef enum {NONE, STRING, BOOL, INT, INT_ENUM} OptionType;

   public: std::string _name;
   public: bool _is_set;
   public: OptionType _type;

   public: _Option();
   public: virtual ~_Option() {};
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
         return true;
      }
      return false;
   }
};


typedef Option<std::string> StringOption;
typedef Option<bool> BoolOption;


} }
#endif
