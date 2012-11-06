#ifndef _MEM__FS__PATH__HPP_
#define _MEM__FS__PATH__HPP_


#include <string>
#include <utility>


namespace mem { namespace fs { namespace path {

std::pair<std::string, std::string>
split (std::string sRawPath);

} } }


#endif
