#include "mem/log/XmlFormatter.hpp"


namespace mem { namespace log {

XmlFormatter::XmlFormatter ()
{
   setId("xml");
}

std::string
XmlFormatter::_formatLevel (MessageLevel lvl)
{
   std::string ret = "";
   switch (lvl)
   {
      case UNKNOWN:     ret += "Unknown"; break;
      case INFO:        ret += "Info"; break;
      case DEBUG:       ret += "Debug"; break;
      case WARNING:     ret += "Warning"; break;
      case ERROR:       ret += "Error"; break;
      case FATAL_ERROR: ret += "FatalError"; break;
      default:
         ret += "???";
   }
   return ret;
}

std::string
XmlFormatter::format (Message* msg)
{
   std::string res = "";

   res += "<message";
   res += " level=\"" + _formatLevel(msg->Level());
   res += "\"";
   res += ">\n";

   if (msg->PrimaryText().size() != 0)
   {
      res += "\t<title>" + msg->PrimaryText() + "</title>\n";
   }

   if (msg->SecondaryText().size() != 0)
   {
      res += "\t<description>" + msg->SecondaryText() + "</description>\n";
   }

   res += "</message>\n";
   return res;
}

std::string
XmlFormatter::formatStart ()
{
   return "<log>\n";
}

std::string
XmlFormatter::formatEnd ()
{
   return "</log>\n";
}


} }
