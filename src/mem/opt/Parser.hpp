#ifndef _MEM__OPT__PARSER__HPP_
#define _MEM__OPT__PARSER__HPP_


#include <stdio.h>
#include <stack>
#include <string>
#include <vector>
#include "mem/log/Logger.hpp"
#include "mem/opt/Options.hpp"


namespace mem { namespace opt {


class Parser
{
   public: std::vector<std::string> _params;
   public: log::Logger* _logger;
   public: opt::Options* _opts;

   public: void parse (int argc, char** argv, log::Logger* log, Options* opts);
   public: void _setOpt (std::string name, std::string value);
};


} }


#endif
