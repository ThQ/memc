#ifndef _MEM__ST__PATH__HPP_
#define _MEM__ST__PATH__HPP_


#include <string>

namespace mem { namespace st {

class Path : public std::string
{
   public: size_t _last_dot_pos;

   public: Path(std::string path);
   public: std::string next_name ();
   public: void reset ();
};


}}


#endif

