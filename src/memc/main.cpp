#include "memc/Compiler.hpp"


int main (int argc, char** argv)
{
   DEBUG_PRINT("[Running in DEBUG mode]\n");

   memc::opt::Options opts;
   opts.addStrOpt("--dump-ast-xml", "",
      "Dump the Abstract Syntax Tree as XML");
   opts.addStrOpt("--emit-llvm-bc", "",
      "Emit LLVM bytecode");
   opts.addStrOpt("--log-formatter", "",
      "Set the log formatter");
   opts.addIntEnumOpt("--log-level", "",
      "Set the minimum log level")
      ->bind("unknown", log::UNKNOWN)
      ->bind("debug", log::DEBUG)
      ->bind("info", log::INFO)
      ->bind("warning", log::WARNING)
      ->bind("error", log::ERROR)
      ->bind("fatal-error", log::FATAL_ERROR);
   opts.addBoolOpt("--help", "",
      "Show help");
   opts.addStrOpt("--output", "",
      "Path to the output file");
   opts.addBoolOpt("--version", "",
      "Show version");
   opts.addStrOpt("--dump-st-xml", "",
      "Dump the Symbol Table as XML");
   opts.parse(argc, argv);

   memc::Compiler compiler;
   compiler.setOptions(&opts);
   compiler.run();

   return compiler.isBuildSuccessful() ? 0 : 1;
}
