#include <iostream>
#include <fstream>


#include "mem/Compiler.hpp"


int main (int argc, char** argv)
{
   Compiler memc;

   opt::Options* opt = memc.gOptions();
   opt->set("ast.dump.file", "/home/thomas/mem_ast.xml");
   opt->set("st.dump.xml", "/home/thomas/mem_st.xml");
   opt->set("log.level", "debug");

   memc.fm.appendPath("/home/thomas/code/mem/libs");

   memc.compile(argv[1]);

   return 0;
}
