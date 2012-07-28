#include "mem/tool/Toolbox.hpp"


namespace mem {


Toolbox::Toolbox ()
{
}

std::string
Toolbox::find (ToolName name)
{
   std::string cmd;
   std::string alias;
   std::vector<std::string> aliases;

   switch (name)
   {
      case ASSEMBLER:
         aliases.push_back("as");
         break;

      case GCC:
         aliases.push_back("gcc");
         break;

      case LINKER:
         aliases.push_back("ld");
         break;

      case LLVM_COMPILER:
         aliases.push_back("llc");
         aliases.push_back("llc-3.0");
         break;

      case LLVM_ASSEMBLER:
         aliases.push_back("llvm-as");
         aliases.push_back("llvm-as-3.0");
         break;

      case LLVM_LINKER:
         aliases.push_back("llvm-ld");
         aliases.push_back("llvm-ld-3.0");
         break;

      default:
         DEBUG_PRINTF("Unsupported tool {id: %d}\n", name);
         assert(false);
   }

   if (aliases.size() != 0)
   {
      cmd = findCommand(name, aliases);
   }

   return cmd;
}

std::string
Toolbox::findCommand (ToolName id, std::vector<std::string> commands)
{
   std::string cmd = "";
   for (size_t i=0; i < commands.size(); ++i)
   {
      if (hasCommand("which " + commands[i])) // FIXME This is linux specific
      {
         _tools[id] = commands[i];
         cmd = commands[i];
      }
   }
   return cmd;
}

bool
Toolbox::has (ToolName id)
{
   return _tools.find(id) != _tools.end();

}

int
Toolbox::run (ToolName id, std::string args)
{
   std::string full_cmd = _tools[id] + " " + args;
   return system(full_cmd.c_str());
}


}
