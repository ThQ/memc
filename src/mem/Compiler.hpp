#ifndef _MEM__COMPILER__HPP_
#define _MEM__COMPILER__HPP_


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <queue>
#include <vector>
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Node.hpp"
#include "mem/ast/dumper/XmlDumper.hpp"
#include "mem/ast/visitor/BlockTypesChecker.hpp"
#include "mem/ast/visitor/CheckValidity.hpp"
#include "mem/ast/visitor/FindClasses.hpp"
#include "mem/ast/visitor/FindEntryPoint.hpp"
#include "mem/ast/visitor/FindUse.hpp"
#include "mem/ast/visitor/Prechecker.hpp"
#include "mem/ast/visitor/TopTypesChecker.hpp"
#include "mem/ast/visitor/TypeMatch.hpp"
#include "mem/codegen/llvm/Codegen.hpp"
#include "mem/fs/File.hpp"
#include "mem/fs/FileManager.hpp"
#include "mem/lang/Bison.hpp"
#include "mem/log/ConsoleFormatter.hpp"
#include "mem/log/ConsoleLogger.hpp"
#include "mem/opt/Options.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/st/visitor/DepBuilder.hpp"
#include "mem/st/visitor/XmlDumper.hpp"
#include "mem/Util.hpp"


extern int yyparse(mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger& logger, mem::fs::File* file);
extern FILE* yyin;
extern void reset_lexer();
extern mem::fs::File* yyfile;


namespace mem {


class Compiler
{
   public: typedef enum {NO, XML} StDumpFormat;

   public: ast::node::Root ast;
   public: std::vector<ast::visitor::Visitor*> ast_visitors;
   public: std::vector<st::visitor::Visitor*> st_visitors;
   public: fs::FileManager fm;
   public: log::ConsoleLogger logger;
   public: std::queue<std::string> _parse_queue;
   public: st::SymbolTable symbols;

   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------

   public: opt::Options _opts;
   public: opt::Options* gOptions () {return &_opts;}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Compiler();

   /**
    * Destructor.
    */
   ~Compiler();

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   /**
    * Appends an AST visitor to the visitor list (FIFO).
    */
   inline void
   addAstVisitor (ast::visitor::Visitor* visitor){ast_visitors.push_back(visitor);}

   /**
    * Appends an ST visitor to the visitor list (FIFO).
    */
   inline void
   addStVisitor (st::visitor::Visitor* visitor){st_visitors.push_back(visitor);}

   /**
    * Starts a compiling job starting with an entry file.
    */
   void
   compile (char* file_path);

   void
   dumpAst ();

   void
   dumpSt ();

   void
   emitCode ();

   /**
    * Returns true if no warning nor fatal errors have been emitted.
    */
    bool
    isBuildSuccessful () const {return logger._n_warnings == 0 && logger._n_fatal_errors ==0;}

   /**
    * Parses a file given its path.
    */
   void
   parse (std::string file_path);

   /**
    * Prints a compilation summary to stdout.
    */
   void
   printBuildSummary ();

   /**
    * Parses each file in the parse queue until there's nothing left.
    */
   void
   processParseQueue ();

   void
   runAstVisitors ();

   void
   runStVisitors ();

   void
   setUpOptions ();
};


}


#endif
