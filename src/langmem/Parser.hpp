#ifndef _LANGMEM__PARSER__HPP_
#define _LANGMEM__PARSER__HPP_


#include "langmem/Tokenizer.hpp"
#include "langmem/Bison.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/fs/File.hpp"
#include "mem/log/Logger.hpp"
#include "mem/st/SymbolTable.hpp"


namespace langmem {


class Parse
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   Parse();


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   SETTER(SymbolTable, mem::st::SymbolTable*) {_st = val;}

   SETTER(Logger, mem::log::Logger*) {_logger = val;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   bool
   setup ();

   mem::ast::node::File*
   parse (mem::fs::File* file);

   bool
   tearDown ();


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   mem::st::SymbolTable* _st;
   mem::log::Logger* _logger;

};

//extern FILE* yyin;
//extern mem::fs::File* yyfile;

}

extern int yyparse(mem::ast::node::File* ast, mem::st::SymbolTable* symbols, mem::log::Logger* logger, mem::fs::File* file);

#endif
