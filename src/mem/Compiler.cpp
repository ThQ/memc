#include "mem/Compiler.hpp"


namespace mem {


Compiler::Compiler ()
{
   _logger = new log::ConsoleLogger();
   _logger->setFormatter(new log::ConsoleFormatter());

   _opts = NULL;

   gTOKENIZER.setLogger(_logger);

   addAstVisitor(new ast::visitor::UseAlias());
   addAstVisitor(new ast::visitor::Prechecker());
   addAstVisitor(new ast::visitor::FindClasses());
   addAstVisitor(new ast::visitor::TopTypesChecker());
   addAstVisitor(new ast::visitor::BlockTypesChecker());
   addAstVisitor(new ast::visitor::TypeMatch());
   addAstVisitor(new ast::visitor::CheckValidity());
   addAstVisitor(new ast::visitor::FindEntryPoint());

   st::util::setupBool(this->symbols, this->symbols.gCoreTypes());
   st::util::setupBugType(this->symbols, this->symbols.gCoreTypes());
   st::util::setupInts(this->symbols, this->symbols.gCoreTypes());
   st::util::setupVoid(this->symbols, this->symbols.gCoreTypes());
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
Compiler::dumpAst ()
{
   if (_opts->isSet("--dump-ast-xml"))
   {
      std::string dump_path = _opts->getStr("--dump-ast-xml");

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
   if (_opts->hasArguments())
   {
      std::string llvm_ir_path = "./mem.bc";
      std::string bin_path = "./mem.out";

      if (_opts->isSet("--emit-llvm-bc"))
      {
         llvm_ir_path = _opts->getStr("--emit-llvm-bc");
      }

      if (_opts->isSet("--output"))
      {
         bin_path = _opts->getStr("--output");
      }

      mem::codegen::llvm_::Codegen cg;
      cg.SymbolTable(&symbols);
      cg.gen(&ast);

      // Dump LLVM bytecode
      std::ofstream bc_file;
      bc_file.open(llvm_ir_path.c_str());
      bc_file << cg.getLlvmByteCode();
      bc_file.close();

      _logger->debug("LLVM ByteCode dumped to %s", llvm_ir_path.c_str());

      // Generate native code
      std::string out_s = llvm_ir_path  + ".s";
      std::string out_as = llvm_ir_path + ".as";

      tool::CommandChain cc (_tools);
      cc.run(Toolbox::LLVM_COMPILER, "-o=" + out_s + " " + llvm_ir_path)
         ->then(Toolbox::GCC, out_s + " -o " + bin_path);

      if (cc.Status() == 0)
      {
         _logger->debug("Binary generated as %s", bin_path.c_str());
      }
      else
      {
         _logger->fatalError("Couldn't generate binary as %s",
            bin_path.c_str());
      }
   }
}

void
Compiler::parse (std::string file_path)
{
   _logger->debug("[%s] parsing...", file_path.c_str());

   std::string ns_name = Util::getNamespaceNameFromPath(file_path);
   std::vector<std::string> ns_parts = Util::split(ns_name, '.');
   st::Namespace* file_sym = st::util::createNamespace(symbols._root, ns_parts);
   assert(file_sym != NULL);

   std::vector<std::string> paths_tried;

   fs::File* file = fm.tryOpenFile(file_path, paths_tried);

   if (file != NULL)
   {
      ast::node::File* file_node = new ast::node::File();
      file_node->setBoundSymbol(file_sym);
      file_node->setId(ns_name);
      file_node->setIncludePath(file->_include_path);
      file_node->setPath(file_path);
      ast.pushChild(file_node);

      // TODO We are actually reading each file twice, lang::Tokenizer should
      // populate fs::File
      gTOKENIZER.setInputFile(file->gPath());
      gTOKENIZER.reset();
      yyparse(this->fm, file_node, this->symbols, _logger, file);

      ast::visitor::FindUse find_use;
      _logger->debug("Searching for use statements", "");
      find_use.visit_preorder(file_node);
      for (size_t i = 0; i < find_use._uses.size(); ++i)
      {
         if (ns_name == find_use._uses[i])
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
      msg->setSecondaryText(description);
      _logger->log(msg);
   }
}

void
Compiler::printBuildSummary ()
{
   std::ostringstream sec_text;

   if (_logger->FatalErrorCount() > 0)
   {
      sec_text << "Fatal errors: ";
      sec_text << _logger->FatalErrorCount();
      sec_text << "\n";
   }

   if (_logger->ErrorCount() > 0)
   {
      sec_text << "Errors: ";
      sec_text << _logger->ErrorCount();
      sec_text << "\n";
   }

   if (_logger->WarningCount() > 0)
   {
      sec_text << "Warnings: ";
      sec_text << _logger->WarningCount();
      sec_text << "\n";
   }

   if (isBuildSuccessful())
   {
      _logger->info("Build SUCCESSFUL", "");
   }
   else
   {
      log::Message* err = new log::FatalError();
      err->setPrimaryText("Build FAILED");
      err->setSecondaryText(sec_text.str());
      _logger->log(err);
   }
}

void
Compiler::printUsage (std::ostream& out)
{
   out << "USAGE: ";
   out << PACKAGE_NAME;
   out << " [OPTIONS] <input>\n\n";
   out << "OPTIONS:\n";

   _opts->dump(out);

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
Compiler::run ()
{
   std::string formatter_id = _opts->getStr("--log-formatter");

   if (formatter_id == "xml")
   {
      _logger->setFormatter(new log::XmlFormatter());
   }
   _logger->begin();

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
      std::cout << " (" __DATE__ " " __TIME__ ")";
      IF_DEBUG
      {
         std::cout << " [DEBUG]";
      }
      std::cout << "\n";
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
      //runStVisitors();

      dumpAst();
      dumpSt();

      if (isBuildSuccessful()) emitCode();

      printBuildSummary();
   }

   _logger->finish();

   llvm::llvm_shutdown();
}

void
Compiler::runAstVisitors ()
{
   for (size_t i=0;
      i < ast_visitors.size() && _logger->FatalErrorCount() == 0 && _logger->ErrorCount()==0; ++i)
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
