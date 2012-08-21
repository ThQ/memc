#ifndef _MEMC__TOOLBOX__HPP_
#define _MEMC__TOOLBOX__HPP_


#include <map>
#include <stdlib.h>
#include <string>
#include <vector>
#include "mem/ss.hpp"

namespace memc {


class Toolbox
{
   public:

   typedef enum {ASSEMBLER, GCC, LINKER, LLVM_COMPILER, LLVM_ASSEMBLER, LLVM_LINKER} ToolName;

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------

   protected:

   std::map<ToolName, std::string> _tools;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   Toolbox ();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   bool
   has (ToolName name);

   std::string
   findCommand (ToolName alias, std::vector<std::string> commands);

   std::string
   find(ToolName name);

   bool
   hasCommand (std::string cmd)
   {
      return system(("which " + cmd).c_str()) == 0;
   }

   int
   run (ToolName id, std::string args);
};


}

#endif
