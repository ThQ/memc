#include "mem/fs/path.hpp"


namespace mem { namespace fs { namespace path {


std::pair<std::string, std::string>
split (std::string sRawPath)
{
   std::pair<std::string, std::string> res;
   size_t iLastSepPos = sRawPath.rfind("/");

   if (iLastSepPos == sRawPath.size() - 1)
   {
      res.first = sRawPath;
      res.second = "";
   }
   else
   {
      res.first = sRawPath.substr(0, iLastSepPos + 1);
      res.second = sRawPath.substr(iLastSepPos + 1, sRawPath.size());
   }
   return res;
}

} } }
