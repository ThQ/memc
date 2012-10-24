#ifndef _MEMC__COMPILER__HPP_
#define _MEMC__COMPILER__HPP_


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <queue>
#include <vector>
#include "config.h"
#include "codegen/llvm/Codegen.hpp"
#include "langmem/Parser.hpp"
#include "mem/ast/macro/PtrMacros.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Node.hpp"
#include "mem/ast/visitor/BlockTypesChecker.hpp"
#include "mem/ast/visitor/CheckValidity.hpp"
#include "mem/ast/visitor/CoherenceChecker.hpp"
#include "mem/ast/visitor/Ctor.hpp"
#include "mem/ast/visitor/Decorate.hpp"
#include "mem/ast/visitor/FindClasses.hpp"
#include "mem/ast/visitor/FindEntryPoint.hpp"
#include "mem/ast/visitor/FindUse.hpp"
#include "mem/ast/visitor/Prechecker.hpp"
#include "mem/ast/visitor/Stats.hpp"
#include "mem/ast/visitor/TopTypesChecker.hpp"
#include "mem/ast/visitor/TypeMatch.hpp"
#include "mem/ast/visitor/UseAlias.hpp"
#include "mem/ast/visitor/XmlDumper.hpp"
#include "mem/decorator/External.hpp"
#include "mem/decorator/Overriding.hpp"
#include "mem/decorator/Require.hpp"
#include "mem/decorator/Virtual.hpp"
#include "mem/fs/File.hpp"
#include "mem/fs/FileManager.hpp"
#include "mem/log/ConsoleFormatter.hpp"
#include "mem/log/ConsoleLogger.hpp"
#include "mem/log/XmlFormatter.hpp"
#include "mem/st/Alias.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/st/visitor/DepBuilder.hpp"
#include "mem/st/visitor/XmlDumper.hpp"
#include "mem/Util.hpp"
#include "memc/tool/CommandChain.hpp"
#include "memc/tool/Toolbox.hpp"
#include "memc/opt/Options.hpp"


namespace memc {


class Compiler
{
   public: typedef enum {NO, XML} StDumpFormat;

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   mem::ast::node::Root ast;
   std::vector<mem::ast::visitor::Visitor*> ast_visitors;
   std::vector<mem::st::visitor::Visitor*> st_visitors;
   mem::fs::FileManager fm;
   mem::log::ConsoleLogger* _logger;
   opt::Options* _opts;
   std::queue<std::string> _parse_queue;
   mem::st::SymbolTable symbols;
   Toolbox _tools;
   mem::decorator::DecoratorMap _decorators;
   langmem::Parse* _parser;

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
   Compiler(opt::Options* opts);

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
   addAstVisitor (mem::ast::visitor::Visitor* visitor){ast_visitors.push_back(visitor);}

   void
   addDecorator (mem::decorator::Decorator* decorator);

   void
   addMacro (mem::ast::macro::Macro* macro);

   /**
    * Append an ST visitor to the visitor list (FIFO).
    */
   inline void
   addStVisitor (mem::st::visitor::Visitor* visitor){st_visitors.push_back(visitor);}

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
