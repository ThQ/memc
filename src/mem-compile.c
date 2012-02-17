#include <iostream>
#include <fstream>

#include "macro.h"
#include "mem/ast/dumper/XmlDumper.hpp"
#include "mem/Compiler.hpp"
#include "mem/log/MessageLevel.hpp"
#include "mem/st/dumper/TextDumper.hpp"


int main (int argc, char** argv)
{
   Compiler memc;
   memc.logger._level = mem::log::DEBUG;
   memc.fm._path.push_back("/home/thomas/code/mem/libs");
   memc.compile(argv[1]);

   mem::ast::dumper::XmlDumper dumper;
   std::ofstream ast_dump_file;
   ast_dump_file.open("/home/thomas/mem_ast.xml");
   dumper.dump_to(&memc.ast, ast_dump_file);
   ast_dump_file.close();

   mem::st::dumper::TextDumper st_dumper;
   std::ofstream st_dump_file;
   st_dump_file.open("/home/thomas/mem_st.xml");
   st_dumper.dump_to(memc.symbols._root, st_dump_file);
   st_dump_file.close();

   return 0;
}
