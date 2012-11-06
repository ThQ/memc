#include "memc/Compiler.hpp"


namespace memc {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Compiler::Compiler (opt::Options* opts)
{
   mem::log::Formatter* formatter = NULL;

   // TODO: Should use a factory or something here
   if (opts->getStr("--log-formatter") == "test-friendly")
   {
      formatter = new mem::log::TestFriendlyFormatter();
   }
   else if (opts->getStr("--log-formatter") == "xml")
   {
      formatter = new mem::log::XmlFormatter();
   }
   else
   {
      mem::log::ConsoleFormatter* cons_formatter = new mem::log::ConsoleFormatter();

      if (opts->getStrEnum("--color") == "yes")
      {
         cons_formatter->setColorsEnabled(true);
      }
      else
      {
         cons_formatter->setColorsEnabled(false);
      }

      formatter = cons_formatter;
   }

   _logger = new mem::log::ConsoleLogger();
   _logger->setFormatter(formatter);

   _parser = new langmem::Parse();
   _parser->setLogger(_logger);
   _parser->setSymbolTable(&symbols);

   _opts = opts;

   addDecorator(new mem::decorator::External());
   addDecorator(new mem::decorator::Overriding());
   addDecorator(new mem::decorator::Require());
   addDecorator(new mem::decorator::Virtual());

   addMacro(new mem::ast::macro::PtrMacros());

   // Setup AST visitors
   addAstVisitor(new mem::ast::visitor::CoherenceChecker());
   addAstVisitor(new mem::ast::visitor::UseAlias());
   addAstVisitor(new mem::ast::visitor::Prechecker());
   addAstVisitor(new mem::ast::visitor::FindClasses());
   addAstVisitor(new mem::ast::visitor::TopTypesChecker());
   addAstVisitor(new mem::ast::visitor::Decorate(_decorators));
   addAstVisitor(new mem::ast::visitor::Ctor());
   addAstVisitor(new mem::ast::visitor::BlockTypesChecker());
   addAstVisitor(new mem::ast::visitor::CoherenceChecker());
   addAstVisitor(new mem::ast::visitor::CheckValidity());
   addAstVisitor(new mem::ast::visitor::FindEntryPoint());
   addAstVisitor(new mem::ast::visitor::Stats());

   mem::st::util::setupBool(this->symbols, this->symbols.gCoreTypes());
   mem::st::util::setupBugType(this->symbols, this->symbols.gCoreTypes());
   mem::st::util::setupInts(this->symbols, this->symbols.gCoreTypes());
   mem::st::util::setupVoid(this->symbols, this->symbols.gCoreTypes());
}

Compiler::~Compiler ()
{
   delete _logger;
   delete _parser;

   mem::decorator::DecoratorMap::iterator i;

   for (i = _decorators.begin(); i != _decorators.end(); ++i)
   {
      delete i->second;
   }

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


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
Compiler::addDecorator (mem::decorator::Decorator* dec)
{
   DEBUG_REQUIRE (dec != NULL);

   if (_decorators.find(dec->Name()) == _decorators.end())
   {
      _decorators[dec->Name()] = dec;
   }
}

void
Compiler::addMacro (mem::ast::macro::Macro* macro)
{
   DEBUG_REQUIRE (macro != NULL);

   mem::st::Macro* macro_sym = macro->getSymbol();
   symbols.System()->addChild(macro_sym);
   delete macro;
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
      _logger->info("AST dumped to %s (XML)", dump_path.c_str());
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

      mem::st::visitor::XmlDumper dumper;
      dumper._out = &st_dump_file;
      dumper.setup();
      dumper.visitPreorder(symbols.Root());

      st_dump_file.close();
      _logger->info("SymbolTable dumped to %s (XML)", dump_path.c_str());
   }
}

void
Compiler::emitCode ()
{
   if (_opts->hasArguments())
   {
#ifdef HAVE_LLVM
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

      codegen::llvm_::Codegen cg;
      cg.setSymbolTable(&symbols);
      cg.gen(&ast);

      // Dump LLVM bytecode
      std::ofstream bc_file;
      bc_file.open(llvm_ir_path.c_str());
      bc_file << cg.getLlvmByteCode();
      bc_file.close();

      _logger->info("LLVM ByteCode dumped to %s", llvm_ir_path.c_str());

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
#endif // HAVE_LLVM
   }
}

void
Compiler::parse (mem::ast::node::Use* nodeUse)
{
   std::string sFileNamespace = nodeUse->Value();
   std::string sFilePath = mem::Util::getPathFromNamespace(sFileNamespace) + ".mem";

   _logger->debug("Parsing `%s'", sFilePath.c_str());

   std::vector<std::string> ns_parts = mem::Util::split(sFileNamespace, '.');
   mem::st::Namespace* symFileNamespace = mem::st::util::createNamespace(symbols.Home(), ns_parts);
   assert(symFileNamespace != NULL);

   std::vector<std::string> paths_tried;

   mem::fs::File* file = fm.tryOpenFile(sFilePath, paths_tried);

   if (file != NULL)
   {
      gTOKENIZER.reset();
      gTOKENIZER.setInputFile(file->Path());

      mem::ast::node::File* nodeFile = NULL;
      nodeFile = _parser->parse (file);
      nodeFile->setBoundSymbol(symFileNamespace);
      nodeFile->setId(sFileNamespace);
      nodeFile->setIncludePath(file->IncludePath());
      nodeFile->setPath(sFilePath);
      ast.addChild(nodeFile);

      _findUses(nodeFile);
   }
   else
   {
      std::string description = "We tried :\n";
      std::vector<std::string>::size_type i;
      for (i=0; i<paths_tried.size(); ++i)
      {
         description.append("* " + paths_tried[i] + "\n");
      }

      mem::log::Message* msg = new mem::log::Error();
      msg->formatMessage("Couldn't open file `%s'", sFilePath.c_str());
      if (nodeUse->IdNode() != NULL)
      {
         msg->setPosition(nodeUse->IdNode()->copyPosition());
      }
      msg->setSecondaryText(description);
      _logger->log(msg);
   }
}

void
Compiler::printUsage (std::ostream& out)
{
   out << "USAGE: ";
#ifdef PACKAGE_NAME
   out << PACKAGE_NAME;
#else
   out << "?";
#endif
   out << " [OPTIONS] <input>\n\n";
   out << "OPTIONS:\n";

   _opts->dump(out);
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
   _logger->begin();

   // Need to set this before parsing command line arguments because it can
   // raise warnings
#ifdef NDEBUG
   _logger->setLevel(mem::log::INFO);
#else
   _logger->setLevel(mem::log::DEBUG);
#endif

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
      std::cout << "\n\n";
      std::cout << "       Build date: " << __DATE__ << "\n";
      std::cout << "       Build time: " << __TIME__ << "\n";
      std::cout << "         Compiler: " << COMPILER_NAME << "\n";
      std::cout << "   Compiler flags: " << COMPILER_FLAGS << "\n";
      std::cout << "          Version: " << PACKAGE_VERSION << "\n";
      std::cout << "             Yacc: " << YACC_EXE << "\n";
   }
   else if (_opts->isSet("--help"))
   {
      printUsage(std::cout);
   }
   else if (_opts->hasArguments())
   {
      std::pair<std::string, std::string> FilePath = mem::fs::path::split(_opts->getArgument(0));

      fm.appendPath(FilePath.first);

      mem::ast::node::Use nodeUse;
      nodeUse.setValue(mem::Util::getNamespaceFromPath(FilePath.second));
      _parse_queue.push(&nodeUse);

      processParseQueue();

      runAstVisitors();
      //runStVisitors();

      dumpAst();
      dumpSt();

      if (isBuildSuccessful()) emitCode();

      _logBuildSummary();
   }

   _logger->finish();

}

void
Compiler::runAstVisitors ()
{
   bool bNoErrors = _logger->FatalErrorCount()==0 && _logger->ErrorCount()==0;

   for (size_t i=0; i < ast_visitors.size() && bNoErrors; ++i)
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
      st_visitors[i]->visitPreorder(symbols.Root());
      st_visitors[i]->tearDown();
   }
}


//-----------------------------------------------------------------------------
// PROTECTED FUNCTIONS
//-----------------------------------------------------------------------------

void
Compiler::_findUses (mem::ast::node::File* nodeFile)
{
   _logger->debug("Searching for use statements", "");

   mem::ast::visitor::FindUse use_finder;
   use_finder.visit_preorder(nodeFile);

   std::vector<mem::ast::node::Use*> uses = use_finder._uses;

   for (size_t i = 0; i < uses.size(); ++i)
   {
      if (nodeFile->Id() != uses[i]->Value())
      {
         _parse_queue.push(uses[i]);
      }
      // Trying to include itself
      else
      {
         mem::log::AutoInclude* err = new mem::log::AutoInclude();
         err->setFilePath(nodeFile->Path());
         err->format();
         _logger->log(err);
      }
   }
}

void
Compiler::_logBuildSummary ()
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
      mem::log::BuildFailed* err = new mem::log::BuildFailed();
      err->setSecondaryText(sec_text.str());
      err->format();
      _logger->log(err);
   }
}

}
