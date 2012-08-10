#ifndef _MEM__COMPILER__HPP_
#define _MEM__COMPILER__HPP_


#include <iostream>
#include <llvm/Support/ManagedStatic.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <queue>
#include <vector>
#include "config.h"
#include "mem/ast/macro/PtrMacros.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Node.hpp"
#include "mem/ast/visitor/BlockTypesChecker.hpp"
#include "mem/ast/visitor/CheckValidity.hpp"
#include "mem/ast/visitor/Decorate.hpp"
#include "mem/ast/visitor/FindClasses.hpp"
#include "mem/ast/visitor/FindEntryPoint.hpp"
#include "mem/ast/visitor/FindUse.hpp"
#include "mem/ast/visitor/Prechecker.hpp"
#include "mem/ast/visitor/TopTypesChecker.hpp"
#include "mem/ast/visitor/TypeMatch.hpp"
#include "mem/ast/visitor/UseAlias.hpp"
#include "mem/ast/visitor/XmlDumper.hpp"
#include "mem/codegen/llvm/Codegen.hpp"
#include "mem/decorator/External.hpp"
#include "mem/decorator/Overriding.hpp"
#include "mem/decorator/Require.hpp"
#include "mem/decorator/Virtual.hpp"
#include "mem/fs/File.hpp"
#include "mem/fs/FileManager.hpp"
#include "mem/lang/Bison.hpp"
#include "mem/log/ConsoleFormatter.hpp"
#include "mem/log/ConsoleLogger.hpp"
#include "mem/log/XmlFormatter.hpp"
#include "mem/opt/Options.hpp"
#include "mem/st/Alias.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/st/visitor/DepBuilder.hpp"
#include "mem/st/visitor/XmlDumper.hpp"
#include "mem/tool/CommandChain.hpp"
#include "mem/tool/Toolbox.hpp"
#include "mem/Util.hpp"


extern int yyparse(mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger* logger, mem::fs::File* file);
extern FILE* yyin;
extern void reset_lexer();
extern mem::fs::File* yyfile;


namespace mem {


class Compiler
{
   public: typedef enum {NO, XML} StDumpFormat;

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   ast::node::Root ast;
   std::vector<ast::visitor::Visitor*> ast_visitors;
   std::vector<st::visitor::Visitor*> st_visitors;
   fs::FileManager fm;
   log::ConsoleLogger* _logger;
   opt::Options* _opts;
   std::queue<std::string> _parse_queue;
   st::SymbolTable symbols;
   Toolbox _tools;
   decorator::DecoratorMap _decorators;

   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(Options, opt::Options*) {return _opts;}
   SETTER(Options, opt::Options*) {_opts = val;}


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
    * Append an AST visitor to the visitor list (FIFO).
    */
   inline void
   addAstVisitor (ast::visitor::Visitor* visitor){ast_visitors.push_back(visitor);}

   void
   addDecorator (decorator::Decorator* decorator);

   void
   addMacro (ast::macro::Macro* macro);

   /**
    * Append an ST visitor to the visitor list (FIFO).
    */
   inline void
   addStVisitor (st::visitor::Visitor* visitor){st_visitors.push_back(visitor);}

   void
   dumpAst ();

   void
   dumpSt ();

   /**
    * Emit code depending on what the user requested.
    */
   void
   emitCode ();

   /**
    * Return true if no warnings nor fatal errors have been emitted.
    */
   bool
   isBuildSuccessful () const
   {
      return _logger->FatalErrorCount() ==0 &&
         _logger->ErrorCount()==0;
   }

   /**
    * Parse a file given its path.
    */
   void
   parse (std::string file_path);

   /**
    * Print a compilation summary to stdout.
    */
   void
   printBuildSummary ();

   void
   printUsage (std::ostream& out);

   /**
    * Parse each file in the parse queue until there's nothing left.
    */
   void
   processParseQueue ();

   /**
    * Start a compiling job starting with an entry file.
    */
   void
   run ();

   void
   runAstVisitors ();

   void
   runStVisitors ();
};


}


#endif
