#include "mem/log/ConsoleFormatter.hpp"


namespace mem { namespace log {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

ConsoleFormatter::ConsoleFormatter ()
{
   setId("console");
   _colors_enabled = false;
}

ConsoleFormatter::~ConsoleFormatter ()
{
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

std::string
ConsoleFormatter::format (Message* msg)
{
   std::ostringstream res;

   this->_formatMessage(res, msg);

   if (msg->SecondaryText() != "")
   {
      this->_formatDescription(res, msg);
   }

   if (msg->Position() != NULL)
   {
      this->_formatPosition(res, msg->Position());
   }
   return res.str();
}

//-----------------------------------------------------------------------------
// PROTECTED FUNCTIONS
//-----------------------------------------------------------------------------

void
ConsoleFormatter::_formatDescription (std::ostream& str, Message* msg)
{
   std::string sec_text = msg->SecondaryText();

   if (sec_text.length() != 0)
   {
      size_t i;
      size_t last_nl = 0;
      for (i=0; i < sec_text.length(); ++i)
      {
         if (sec_text.data()[i] == '\n')
         {
            str << "     ";
            str << sec_text.substr(last_nl, i-last_nl);
            str << "\n";
            last_nl = i+1;
         }
      }
      if (last_nl != sec_text.size())
      {
         str << "     ";
         str << sec_text.substr(last_nl, sec_text.size()-last_nl);
         str << "\n";
      }
   }
}

void
ConsoleFormatter::_formatLevelId (std::ostream& str, MessageLevel lvl)
{
   switch (lvl)
   {
      case UNKNOWN:
         str << " (?)";
         break;

      case INFO:
         str << " (I)";
         break;

      case DEBUG:
         str << " " << _getLinuxColor("1;30") << "(D)";
         break;

      case WARNING:
         str << " " << _getLinuxColor("1;34") << "(W)";
         break;

      case ERROR:
         str << " " << _getLinuxColor("1;31") << "(E)";
         break;

      case FATAL_ERROR:
         str << " " << _getLinuxColor("1;31") << "(F)";
         break;
   }
}

void
ConsoleFormatter::_formatMessage (std::ostream& str, Message* msg)
{
   _formatLevelId(str, msg->Level());
   str << " " << msg->PrimaryText() << "\033[0m\n";
}

void
ConsoleFormatter::_formatPosition (std::ostream& str, fs::position::Position* pos_a)
{
   fs::position::Range* pos = static_cast<fs::position::Range*>(pos_a);
   if (pos->_file != NULL)
   {
      str << "     @ ";
      str << pos->gFile()->gPath();
      str << ":";
      str << pos->LineStart();
      str << "\n";

      str << "     > ";

      if (pos->LineStart() > 0 && pos->gFile()->isLineInFile(pos->LineStart()-1))
      {
         std::string context_line = pos->gFile()->getLineCstr(pos->LineStart()-1);
         str << context_line;
         str << "\n       ";

         for (size_t i = 1 ; i < context_line.length() ; ++i)
         {
            switch (pos->getTypeAt(i))
            {
               case fs::position::NOTHING: str << " "; break;
               case fs::position::RANGE:   str << "-"; break;
               case fs::position::CURSOR:  str << "^"; break;
            }
         }
         str << "\n";
      }
      else
      {
         str << "<bad line:";
         str << pos->LineStart();
         str << ">\n";
      }
   }
   else
   {
      str << "       @  <invalid file>\n";
   }
}

std::string
ConsoleFormatter::_getLinuxColor (std::string color)
{
   if (_colors_enabled)
   {
      return "\033[" + color + "m";
   }
   return "";
}

} }
