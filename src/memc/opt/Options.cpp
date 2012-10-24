#include "memc/opt/Options.hpp"

namespace memc { namespace opt {


Options::~Options ()
{
   for (OptionMap::iterator i= _options.begin(); i != _options.end(); ++i)
   {
      delete i->second;
      // This is usefull because options are added twice if they have a long
      // and a short name
      i->second = NULL;
   }
}

_Option*
Options::_getOptObject (std::string opt_name)
{
   if (_options.find(opt_name) != _options.end())
   {
      return _options[opt_name];
   }
   return NULL;
}

void
Options::dump (std::ostream& out)
{
   for (OptionMap::iterator i = _options.begin(); i != _options.end(); ++i)
   {
      if (i->second->ShortName().size() != 0)
      {
         out << i->second->ShortName() << "\n";
      }
      out << " " << i->second->LongName();
      switch (i->second->Type())
      {
         case _Option::STRING:
            out << "=<string>\n";
            break;

         case _Option::INT_ENUM:
         {
            EnumOption<int>* opt = static_cast<EnumOption<int>*>(i->second);
            std::map<std::string, int>::iterator i;

            out << "=<";
            for (i = opt->_enum.begin(); i != opt->_enum.end(); ++i)
            {
               if (i != opt->_enum.begin()) out << "|";
               out << i->first.c_str();
            }
            out << ">\n";

            break;
         }
         case _Option::STRING_ENUM:
         {
            EnumOption<std::string>* opt = static_cast<EnumOption<std::string>*>(i->second);
            std::map<std::string, std::string>::iterator i;

            out << "=<";
            for (i = opt->_enum.begin(); i != opt->_enum.end(); ++i)
            {
               if (i != opt->_enum.begin()) out << "|";
               out << i->first.c_str();
            }
            out << ">\n";

            break;
         }

         default:
            out << "\n";
      }
      if (i->second->Description().size() != 0)
      {
         out << "   " << i->second->Description() << "\n";
      }
      out << "\n";
   }
}

bool
Options::isSet (std::string opt_name)
{
   if (_options.find(opt_name) != _options.end())
   {
      return _options.find(opt_name)->second->_is_set;
   }
   return false;
}

void
Options::addOpt (_Option* opt)
{
   _options[opt->LongName()] = opt;
   if (opt->ShortName().size() != 0)
   {
      _options[opt->ShortName()] = opt;
   }
}

void
Options::addBoolOpt (std::string long_name, std::string short_name, std::string desc)
{
   BoolOption* opt = new BoolOption();
   opt->setType(_Option::BOOL);
   opt->setLongName(long_name);
   opt->setShortName(short_name);

   addOpt(opt);
}

void
Options::addStrOpt (std::string long_name, std::string short_name, std::string desc)
{
   StringOption* opt = new StringOption();
   opt->setLongName(long_name);
   opt->setShortName(short_name);
   opt->setDescription(desc);
   opt->setType(_Option::STRING);

   addOpt(opt);
}

void
Options::parse (int argc, char** argv)
{
   // For an option like "--my_option=my_value", the stack will go as :
   // > VOID................................ Found '--'
   // > VOID, OPT_NAME, NAME................ Found '='
   // > VOID, OPT_NAME...................... Found '='
   // > VOID, OPT_VALUE, VALUE_START........ Value starts (no quote)
   // > VOID, OPT_VALUE, VALUE_END.......... Found '\0'
   // > VOID, OPT_VALUE..................... Set option
   // No more character to process

   typedef enum {VOID, OPT, OPT_NAME, OPT_VALUE, NAME, VALUE_START, VALUE_END,
      VALUE_EQ, VALUE_END_QUOTE, PARAM} _State;

   // TODO This is ugly, how to go around quoted params that get swallowed by
   // the shell ?
   std::string arg;
   for (int i = 1; i < argc; ++i)
   {
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

   std::string opt_name="";
   std::string opt_value="";
   int state;
   std::stack<int> stack;
   stack.push(VOID);

   for (size_t i = 0; i < arg.size(); ++i)
   {
      state = stack.top();

      char c = arg[i];
      char c2 = arg[i+1];

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
               opt_name = "--";
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
            set(opt_name, opt_value);
            opt_name = "";
            opt_value = "";
            stack.pop();
            break;

         case PARAM:
            _params.push_back(opt_value);
            opt_value="";
            stack.pop();
            break;

         case NAME:
            switch (c)
            {
               case '\0':
               case '=':
               case ' ':
                  stack.pop();
                  break;

               default:
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
               set(opt_value, "");
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
            else if (c != ' ')
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


bool
Options::set (std::string opt_name, std::string opt_value)
{
   bool is_set = false;
   _Option* opt = _getOptObject(opt_name);
   if (opt != NULL)
   {
      DEBUG_PRINTF("Set option <%s>=<%s> (type=%d)\n", opt_name.c_str(), opt_value.c_str(), opt->_type);

      switch (opt->_type)
      {
         case _Option::STRING:
            is_set = static_cast<StringOption*>(opt)->setVal(opt_value);
            break;

         case _Option::STRING_ENUM:
            is_set = static_cast<EnumOption<std::string>*>(opt)->setVal(opt_value);
            break;

         case _Option::INT_ENUM:
            is_set = static_cast<EnumOption<int>*>(opt)->setVal(opt_value);
            break;

         case _Option::BOOL:
            opt->_is_set = true;
            is_set = true;
            break;

         default:
            DEBUG_PRINTF("Option <%s>=<%s> has unknown type <%d>\n",
               opt_name.c_str(), opt_value.c_str(), opt->_type);
            assert(false);
      }
   }
   else IF_DEBUG
   {
      DEBUG_PRINTF("Option <%s> does not exist.", opt_name.c_str());
      assert(false);
   }
   return is_set;
}


} }
