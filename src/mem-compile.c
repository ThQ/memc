#include "macro.h"
#include "mem/Compiler.hpp"
#include "mem/log/MessageLevel.hpp"


int main (int argc, char** argv)
{
   Compiler memc;
   memc.logger._level = mem::log::WARNING;
   memc.fm._path.push_back("/home/thomas/code/mem/libs");
   memc.compile(argv[1]);
   memc.ast.dump();
   memc.symbols.dump();

   return 0;
}
