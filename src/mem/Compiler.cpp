#include "mem/Compiler.hpp"


namespace mem {


Compiler::Compiler ()
{
   _logger = new log::ConsoleLogger();
   _logger->setFormatter(new log::ConsoleFormatter());

   _opts = NULL;

   gTOKENIZER.setLogger(_logger);

   addAstVisitor(new ast::visitor::Prechecker());
   addAstVisitor(new ast::visitor::FindClasses());
   addAstVisitor(new ast::visitor::TopTypesChecker());
   addAstVisitor(new ast::visitor::BlockTypesChecker());
   addAstVisitor(new ast::visitor::TypeMatch());
   addAstVisitor(new ast::visitor::CheckValidity());
   addAstVisitor(new ast::visitor::FindEntryPoint());

   st::Util::setupBool(this->symbols, this->symbols.gCoreTypes());
   st::Util::setupInts(this->symbols, this->symbols.gCoreTypes());
   st::Util::setupVoid(this->symbols, this->symbols.gCoreTypes());
}

Compiler::~Compiler ()
{
   delete _logger;
   // Delete AST visitors
   for (size_t i = 0; i < ast_visitors.size(); ++i)
   {
      delete ast_visitors[i];
   }

   // Delete ST visitors
   for (size_t i = 0; i < st_visitors.size(); ++i)
   {
      delete st_visitors[i];
   }
}

void
Compiler::compile (int argc, char** argv)
{
   fm.appendPath(".");

   // Need to set this before parsing command line arguments because it can
   // raise warnings
   _logger->setLevel(log::INFO);

   if (_opts->isSet("--log-level"))
   {
      _logger->setLevel(_opts->getInt("--log-level"));
   }

   if (_opts->isSet("--version"))
   {
      std::cout << PACKAGE_NAME " version " PACKAGE_VERSION;
      std::cout << " (" __DATE__ " " __TIME__ ")\n";
   }

   else if (_opts->isSet("--help"))
   {
      printUsage(std::cout);
   }

   else if (_opts->hasArguments())
   {
      _parse_queue.push(_opts->getArgument(0));

      processParseQueue();

      runAstVisitors();
      runStVisitors();

      dumpAst();
      dumpSt();

      if (isBuildSuccessful()) emitCode();

      printBuildSummary();
   }

   llvm::llvm_shutdown();
}

void
Compiler::dumpAst ()
{
   if (_opts->isSet("--dump-ast-xml"))
   {
      std::string dump_path = _opts->getStr("ast.dump.xml");

      std::ofstream dump_file(dump_path.c_str());

      mem::ast::visitor::XmlDumper dumper;
      dumper.Out(&dump_file);
      dumper.setup();
      dumper.visit(&ast);
      dumper.tearDown();

      dump_file.close();
      _logger->debug("AST dumped to %s", dump_path.c_str());
   }
}

void
Compiler::dumpSt ()
{
   if (_opts->isSet("--dump-st-xml"))
   {
      std::string dump_path = _opts->getStr("--dump-st-xml");
      // Open dump file
      // TODO We should have a default output file in case the user did not
      // give one
      std::ofstream st_dump_file(dump_path.c_str());

      st::visitor::XmlDumper dumper;
      dumper._out = &st_dump_file;
      dumper.setup();
      dumper.visitPreorder(symbols._root);

      st_dump_file.close();
      _logger->debug("SymbolTable dumped to %s (XML)", dump_path.c_str());
   }
}

void
Compiler::emitCode ()
{
   std::string out_path;

   if (_opts->isSet("--emit-llvm-bc"))
   {
      out_path = _opts->getStr("--emit-llvm-bc");
      mem::codegen::llvm_::Codegen cg;
      cg.SymbolTable(&symbols);
      cg.gen(&ast);

      std::ofstream bc_file;
      bc_file.open(out_path.c_str());
      bc_file << cg.getLlvmByteCode();
      bc_file.close();

      _logger->debug("LLVM ByteCode dumped to %s", out_path.c_str());
   }
}

void
Compiler::parse (std::string file_path)
{
   _logger->debug("[%s] parsing...", file_path.c_str());

   // @TODO Split it
   st::Namespace* file_sym = st::Util::createNamespace(this->symbols._root, Util::split(Util::stripFileExtension(file_path),'/'));
   assert(file_sym != NULL);

   //reset_lexer();
   std::vector<std::string> paths_tried;

   fs::File* file = fm.tryOpenFile(file_path, paths_tried);

   if (file != NULL)
   {
      std::string ns = file->gPathWithoutInclude();
      mem::Util::path_to_namespace(ns);

      ast::node::File* file_node = new ast::node::File();
      file_node->setBoundSymbol(file_sym);
      file_node->setId(ns);
      file_node->setIncludePath(file->_include_path);
      file_node->setPath(file_path);
      ast.pushChild(file_node);

      // Used by yyparse
      //yyin = fopen(file_path.c_str(), "rb");
      // TODO The file was opened ms before
      // We could open the file only once if we used Bison++
      //assert(yyin != NULL);
      //yyfile = file;
      // TODO We are actually reading each file twice, lang::Tokenizer should 
      // populate fs::File
      gTOKENIZER.setInputFile(file->gPath());
      gTOKENIZER.reset();
      yyparse(this->fm, file_node, this->symbols, _logger, file);

      ast::visitor::FindUse find_use;
      find_use.visit_preorder(file_node);
      for (size_t i = 0; i < find_use._uses.size(); ++i)
      {
         if (ns == find_use._uses[i])
         {
            // FIXME This thing is probably failing, should use a pointer.
            log::Message warn(log::WARNING);
            warn.formatMessage(
               "File {path:%s} is trying to include itself: include ignored.",
               file_path.c_str()
            );
            _logger->log(&warn);
         }
         else
         {
            std::string rel_file_path (find_use._uses[i]);
            mem::Util::namespace_to_path(rel_file_path);
            rel_file_path += ".mem";
            this->_parse_queue.push(rel_file_path);
         }
      }
      //fclose(yyin);
   }
   else
   {
      std::string description = "We tried :\n";
      std::vector<std::string>::size_type i;
      for (i=0; i<paths_tried.size(); ++i)
      {
         description.append("* {path:" + paths_tried[i] + "}\n");
      }

      log::Message* msg = new log::Error();
      msg->formatMessage("Couldn't open file {path:%s}.", file_path.c_str());
      msg->sDescription(description);
      _logger->log(msg);
   }
}

void
Compiler::printBuildSummary ()
{
   std::ostringstream sum;

   if (_logger->FatalErrorCount() > 0)
   {
      sum << _logger->FatalErrorCount();
      sum << " fatal errors, ";
   }

   if (_logger->ErrorCount() > 0)
   {
      sum << _logger->ErrorCount();
      sum << " errors, ";
   }

   if (_logger->WarningCount() > 0)
   {
      sum << _logger->WarningCount();
      sum << " warnings, ";
   }

   if (isBuildSuccessful())
   {
      _logger->info("Build SUCCESSFUL", "");
   }
   else
   {
      _logger->info(sum.str().c_str(), "");
      _logger->fatalError("Build FAILED", "");
   }
}

void
Compiler::printUsage (std::ostream& out)
{
   out << "USAGE: ";
   out << PACKAGE_NAME;
   out << " [OPTIONS] <input>\n\n";
   out << "OPTIONS:\n";
   /*
   std::map<std::string, opt::CliOption*>::iterator i;
   for (i = _opts->_cli_options.begin(); i != _opts->_cli_options.end(); ++i)
   {
      if (i->second != NULL)
      {
         out << " --";
         out << i->second->_cli_name;
         out << " : \n    ";
         out << i->second->_description;
         out << "\n";
      }
   }
   */
}

void
Compiler::processParseQueue ()
{
   while (!_parse_queue.empty())
   {
      parse(_parse_queue.front());
      _parse_queue.pop();
   }
}

void
Compiler::runAstVisitors ()
{
   for (size_t i=0;
      i < ast_visitors.size() && _logger->FatalErrorCount() == 0; ++i)
   {
      _logger->debug("[%s] running...", ast_visitors[i]->_name.c_str());
      ast_visitors[i]->SymbolTable(&symbols);
      ast_visitors[i]->Logger(_logger);
      ast_visitors[i]->setup();
      ast_visitors[i]->visit_preorder(&ast);
      ast_visitors[i]->tearDown();
   }
}

void
Compiler::runStVisitors ()
{
   for (size_t i = 0; i < st_visitors.size(); ++i)
   {
      _logger->debug("[%s] running...", st_visitors[i]->gNameCstr());
      st_visitors[i]->setup();
      st_visitors[i]->visitPreorder(symbols.gRoot());
      st_visitors[i]->tearDown();
   }
}


}
