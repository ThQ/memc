#include "mem/st/FunctionSignature.hpp"


namespace mem { namespace st {

FunctionSignature::FunctionSignature ()
{
   this->_kind = FUNCTION_SIGNATURE;
}

std::string
FunctionSignature::g_signature ()
{
   std::string res = "";
   for (size_t i = 0 ; i < this->_params.size() ; ++i)
   {
      if (res != "") res += ", ";
      res += this->_params[i]->get_qualified_name();
   }
   res = this->_parent->_name + " (" + res + ")";
   return res;
}

} }
