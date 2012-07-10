#ifndef _MEM__META_DATA__HPP_
#define _MEM__META_DATA__HPP_


#include <map>
#include <string>


namespace mem {


class Metadata
{
   public: std::map<std::string, std::string> _md;

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   inline std::string
   get (std::string md_name) {return _md[md_name];}

   inline bool
   has (std::string md_name) {return _md.find(md_name) != _md.end();}

   bool
   set (std::string md_name, std::string md_value);
};


}


#endif
