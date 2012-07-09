#include "mem/opt/Parser.hpp"


namespace mem { namespace opt {


void
Parser::parse (int argc, char** argv, log::Logger* log, Options* opts)
{
   _logger = log;
   _opts = opts;

   typedef enum {VOID, OPT, OPT_NAME, OPT_VALUE, NAME, VALUE_START, VALUE_END, VALUE_EQ, VALUE_END_QUOTE, PARAM} _State;

   // TODO This is ugly, how to go around quoted params that get swallowed by
   // the shell ?
   std::string arg;
   for (int i = 1; i < argc; ++i)
   {
      //printf("arg#%d = <%s>\n", i, argv[i]);
      if (strlen(argv[i]) >= 2 && !(argv[i][0] == '-' && argv[i][1] == '-'))
      {
            arg.append(1, '"');
            arg.append(argv[i]);
            arg.append(1, '"');
            arg.append(1, ' ');
      }
      else
      {
         arg.append(argv[i]);
         arg.append(1, ' ');
      }
   }
   arg.append(1, '\0');
   //printf("PARAMS=<%s>\n", arg.c_str());
   std::string opt_name;
   std::string opt_value;
   int state;
   std::stack<int> stack;
   stack.push(VOID);

   for (size_t i = 0; i < arg.size(); ++i)
   {
      state = stack.top();

      char c = arg[i];
      char c2 = arg[i+1];
      //printf ("STATE:<%d> -> <%c>,<%c>\n", state, c, c2);

      switch (state)
      {
         case VOID:
            if (c == '\0')
            {
               i = arg.size() + 1;
            }
            if (c=='-' && c2=='-')
            {
               stack.push(OPT_NAME);
               stack.push(NAME);
               ++i;
            }
            else if (c != ' ')
            {
               --i;
               stack.push(PARAM);
               stack.push(VALUE_START);
            }
            break;

         case OPT_NAME:
            //printf("OPT_NAME=<%s>\n", opt_name.c_str());
            if (c == '=')
            {
               stack.push(OPT_VALUE);
               stack.push(VALUE_START);
            }
            else if (c != ' ')
            {
               --i;
               stack.pop();
               stack.push(OPT_VALUE);
               stack.push(VALUE_START);
            }
            break;

         case OPT_VALUE:
            //printf("OPT_VALUE=<%s>\n", opt_value.c_str());
            _setOpt(opt_name, opt_value);
            opt_name = "";
            opt_value = "";
            stack.pop();
            break;

         case PARAM:
            //printf("PARAM=<%s>\n", opt_value.c_str());
            _params.push_back(opt_value);
            opt_value="";
            stack.pop();
            break;

         case NAME:
            if (c == '\0')
            {
               //_setOpt(opt_name, "");
               stack.pop();
            }
            else if (c == '=')
            {
               stack.pop();
            }
            else if (c == ' ')
            {
               stack.pop();
            }
            else
            {
               opt_name.append(1, c);
            }
            break;

         case VALUE_EQ:
            if (c == '=')
            {
               stack.pop();
               stack.push(VALUE_START);
            }
            else if (c != ' ')
            {
               _setOpt(opt_value, "");
               opt_value = "";
               stack.push(VALUE_END);
            }
            break;

         case VALUE_START:
            if (c == '"')
            {
               stack.pop();
               stack.push(VALUE_END_QUOTE);
            }
            else if (c!=' ')
            {
               --i;
               stack.pop();
               stack.push(VALUE_END);
            }
            break;

         case VALUE_END:
            if (c != ' ' && c != '\0')
            {
               opt_value.append(1, c);
            }
            else
            {
               --i;
               stack.pop();
               /*
               _setOpt(opt_name, opt_value);
               opt_name = "";
               opt_value = "";
               state = VOID;
               */
            }
            break;

         case VALUE_END_QUOTE:
            if (c == '"' || c=='\0')
            {
               stack.pop();
            }
            else
            {
               opt_value.append(1, c);
            }
            break;
      }
   }
}

void
Parser::_setOpt(std::string name, std::string value)
{
   if (_opts->hasCliOpt(name))
   {
      //printf("SetOpt <%s>=<%s>\n", name.c_str(), value.c_str());
      _opts->setCli(name, value);
   }
   else
   {
      log::Message* err = new log::Warning();
      err->formatMessage("Unknown option : %s", name.c_str());
      _logger->log(err);
   }
}

} }
