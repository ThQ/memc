#include "mem/st/FunctionSignature.hpp"


namespace mem { namespace st {

FunctionSignature::FunctionSignature ()
{
   this->_kind = FUNCTION_SIGNATURE;
}

std::string
FunctionSignature::gSignature ()
{
   std::string res = "";
   for (size_t i = 0 ; i < this->_params.size() ; ++i)
   {
      if (res != "") res += ", ";
      res += this->_params[i]->gQualifiedName();
   }
   res = this->_parent->_name + " (" + res + ")";
   return res;
}

} }
