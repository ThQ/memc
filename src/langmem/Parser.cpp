#include "langmem/Parser.hpp"


namespace langmem {


Parse::Parse ()
{
   _logger = NULL;
   _st = NULL;
}

mem::ast::node::File*
Parse::parse (mem::fs::File* file)
{
   mem::ast::node::File* file_n = new mem::ast::node::File();

   gTOKENIZER.setInputFile(file->gPath());
   gTOKENIZER.setFsFile(file);
   gTOKENIZER.reset();
   yyparse(file_n, _st, _logger, file);

   return file_n;
}

bool
Parse::setup ()
{
   gTOKENIZER.setLogger(_logger);
   return true;
}


bool
Parse::tearDown ()
{
   return true;
}

}
