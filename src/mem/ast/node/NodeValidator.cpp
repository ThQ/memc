#include "mem/ast/node/NodeValidator.hpp"


namespace mem { namespace ast { namespace node {


NodeValidator::NodeValidator ()
{
   setup();
}

void
NodeValidator::ensure (bool cond)
{
   if (cond == false)
   {
      _is_valid = false;
      _messages.push_back("Unknown");
   }
}

void
NodeValidator::ensure (bool cond, std::string msg)
{
   if (cond == false)
   {
      _is_valid = false;
      _messages.push_back(msg);
   }
}

void
NodeValidator::setup ()
{
   _is_valid = true;
   _messages.clear();
}


} } }
