#include "memc/tool/CommandChain.hpp"


namespace memc { namespace tool {


CommandChain::CommandChain (memc::Toolbox& tb)
{
   _tb = tb;
   _last_status = 0;
}

CommandChain*
CommandChain::then (Toolbox::ToolName alias, std::string args)
{
   if (_last_status == 0)
   {
      run(alias, args);
   }
   return this;
}

CommandChain*
CommandChain::run (Toolbox::ToolName alias, std::string args)
{
   std::string cmd = _tb.find(alias);
   if (cmd.size() != 0)
   {
      _last_status = _tb.run(alias, args);
   }
   else
   {
      _last_status = -1;
   }
   return this;
}


} }
