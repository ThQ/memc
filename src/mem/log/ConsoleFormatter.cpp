#include "mem/log/ConsoleFormatter.hpp"

namespace mem { namespace log {


ConsoleFormatter::ConsoleFormatter ()
{
   this->add_tag("type", format_type_start, format_type_end);
   this->add_tag("symbol", format_type_start, format_type_end);
}

ConsoleFormatter::~ConsoleFormatter ()
{
   this->_tags.clear();
}

void
ConsoleFormatter::add_tag (std::string name, log::TagFunctor fptr_start,
   log::TagFunctor fptr_end)
{
   this->_tags[name] = fptr_start;
   this->_tags["/" + name] = fptr_end;
}

std::string
ConsoleFormatter::format (Message* msg)
{
   std::ostringstream res;

   this->format_message(res, msg);

   bool has_details = msg->_description != "" || msg->_position != NULL;


   if (has_details)
   {
      res << "           --------------------------------------------------------------------\n";
   }
   if (msg->_description != "")
   {
      this->format_description(res, msg);
   }

   if (msg->_position != NULL)
   {
      this->format_position(res, msg->_position);
   }

   if (has_details)
   {
      res << "           --------------------------------------------------------------------\n";
   }
   return res.str();
}

void
ConsoleFormatter::format_description (std::ostringstream& str, Message* msg)
{
   size_t i;
   size_t last_nl = 0;
   for (i=0; i<msg->_description.length(); ++i)
   {
      if (msg->_description.data()[i] == '\n')
      {
         str << "          | ";
         str << msg->_description.substr(last_nl, i-last_nl);
         str << "\n";
         last_nl = i+1;
      }
   }
   if (last_nl != msg->_description.size())
   {
      str << "          | ";
      str << msg->_description.substr(last_nl, msg->_description.size()-last_nl);
      str << "\n";
   }
}

void
ConsoleFormatter::format_level_name (std::ostringstream& str, MessageLevel lvl)
{
   switch (lvl)
   {
      case UNKNOWN:     str << "     ???"; break;
      case INFO:        str << "   INFO"; break;
      case DEBUG:       str << "  DEBUG"; break;
      case WARNING:     str << "\033[0;31mWARNING\033[0m"; break;
      case ERROR:       str << "  \033[1;31mERROR\033[0m"; break;
      case FATAL_ERROR: str << "FATAL_ERROR"; break;
   }

}

void
ConsoleFormatter::format_message (std::ostringstream& str, Message* msg)
{
   this->format_level_name(str, msg->_level);
   str << " : \033[1m";
   str << msg->_message;
   str << "\033[0m\n";
}

void
ConsoleFormatter::format_position (std::ostringstream& str, fs::position::Position* pos)
{
   if (pos->_file != NULL)
   {
      str << "          |\n          | @ {path:";
      str << pos->_file->_path;
      str << "}:";
      str << pos->_line;
      str << "\n";

      if (pos->_line > 0)
      {
         std::string context_line = pos->_file->_lines[pos->_line-1]->c_str();
         str << "          | > ";
         str << context_line;
         str << "\n          |   ";
         for (size_t i = 1 ; i <= context_line.length() ; ++i)
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
   }
   else
   {
      str << "        @  {path:???}\n";
   }
}

const char*
ConsoleFormatter::format_string (const char* message)
{
   std::string sresult;
   char buffer[32] = "";
   size_t buffer_cursor = 0;
   //size_t buffer_len = 0;
   bool buffering = false;
   std::vector<StackElement*> stack;
   StackElement* cur_stack_el = NULL;
   size_t i = 0;
   bool keep_looping = true;
   TagFunctor tag_functor = NULL;

   while (keep_looping)
   {
      char c = message[i];

      switch (c)
      {
         case '\0':
            keep_looping = false;
            break;


         case '{':
            buffering = true;
            cur_stack_el = new StackElement();
            cur_stack_el->start = i;
            stack.push_back(cur_stack_el);
            break;

         case '}':
            buffering = false;
            cur_stack_el = stack.back();
            cur_stack_el->end = i;
            tag_functor = this->get_tag_functor(cur_stack_el->name + "/");
            if (tag_functor != NULL)
            {
               sresult.append(tag_functor());
            }
            delete stack.back();
            stack.pop_back();
            break;

         case ':':
            if (buffering)
            {
               buffer[buffer_cursor] = '\0';
               cur_stack_el->name.assign(buffer);
               tag_functor = this->get_tag_functor(cur_stack_el->name);
               if (tag_functor != NULL)
               {
                  sresult.append(tag_functor());
               }
               buffering = false;
               break;
            }

         default:
            if (buffering)
            {
               buffer[buffer_cursor] = c;
               ++ buffer_cursor;
            }
            else
            {
               sresult += c;
            }
      }
      ++ i;
   }

   for (size_t i = 0 ; stack.size() ; ++i)
   {
      M_DELETE(stack[i]);
   }

   char* result = new char[sresult.size() + 1];
   result = strcpy(result, sresult.c_str());
   return result;
}

const char*
ConsoleFormatter::format_type_end ()
{
   return "\033[0m\0";
}

const char*
ConsoleFormatter::format_type_start ()
{
   return "\033[0;34m\0";
}

log::TagFunctor
ConsoleFormatter::get_tag_functor (std::string name)
{
   if (this->_tags.find(name) != this->_tags.end())
   {
      return this->_tags[name];
   }
   return NULL;
}

} }
