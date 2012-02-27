#include "mem/st/FunctionSignature.hpp"


namespace mem { namespace st {

FunctionSignature::FunctionSignature ()
{
   this->_kind = FUNCTION_SIGNATURE;
   this->_overridden_func = NULL;
}

bool
FunctionSignature::canOverride (FunctionSignature* func_sign)
{
   if (this->_params.size() == func_sign->_params.size())
   {
      for (size_t i = 0 ; i < this->_params.size() ; ++i)
      {
         if (this->_params[i] != func_sign->_params[i])
         {
            return false;
         }
      }
      return true;
   }
   return false;
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
