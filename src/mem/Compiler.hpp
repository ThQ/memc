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
#include "mem/ast/visitor/BlockTypesChecker.hpp"
#include "mem/ast/visitor/FindClasses.hpp"
#include "mem/ast/visitor/FindUse.hpp"
#include "mem/ast/visitor/Prechecker.hpp"
#include "mem/ast/visitor/TopTypesChecker.hpp"
#include "mem/ast/visitor/TypeMatch.hpp"
#include "mem/ast/visitor/VariableTypesChecker.hpp"
#include "fs/File.hpp"
#include "fs/FileManager.hpp"
#include "mem/log/ConsoleFormatter.hpp"
#include "mem/log/ConsoleLogger.hpp"
#include "mem/parser/Bison.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/Util.hpp"


extern int yyparse(mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger& logger, mem::fs::File* file);
extern FILE* yyin;
extern void reset_lexer();
extern mem::fs::File* yyfile;


namespace mem
{
   class Compiler
   {
      public: ast::node::Node ast;
      public: std::vector<ast::visitor::Visitor*> ast_visitors;
      public: fs::FileManager fm;
      public: log::ConsoleLogger logger;
      public: std::queue<std::string> _parse_queue;
      public: st::SymbolTable symbols;

      public: Compiler();
      public: ~Compiler();

      public: void compile (char* file_path);
      public: void parse (std::string file_path);
      public: void processParseQueue();
      public: void registerAstVisitor(ast::visitor::Visitor* visitor);
   };
}

#endif
