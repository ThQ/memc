#include "mem/log/TestFriendlyFormatter.hpp"


namespace mem { namespace log {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

TestFriendlyFormatter::TestFriendlyFormatter ()
{
   setId("test-friendly");
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

std::string
TestFriendlyFormatter::format (Message* msg)
{
   std::ostringstream res;

   res << "(";
   _formatLevelId(res, msg->Level());
   if (msg->Id() != "")
   {
      res << ":" << msg->Id();
   }
   res << ") ";
   res << msg->PrimaryText();
   res << "\n";

   return res.str();
}


//-----------------------------------------------------------------------------
// PROTECTED FUNCTIONS
//-----------------------------------------------------------------------------

void
TestFriendlyFormatter::_formatLevelId (std::ostream& str, MessageLevel lvl)
{
   switch (lvl)
   {
      case UNKNOWN:     str << "?"; break;
      case INFO:        str << "I"; break;
      case DEBUG:       str << "D"; break;
      case WARNING:     str << "W"; break;
      case ERROR:       str << "E"; break;
      case FATAL_ERROR: str << "F"; break;
   }
}


} }
