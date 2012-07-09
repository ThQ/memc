#include "mem/Compiler.hpp"


namespace mem {


Compiler::Compiler ()
{
   this->logger.sFormatter(new log::ConsoleFormatter());

   setUpOptions();

   addAstVisitor(new ast::visitor::Prechecker());
   addAstVisitor(new ast::visitor::FindClasses());
   addAstVisitor(new ast::visitor::TopTypesChecker());
   addAstVisitor(new ast::visitor::BlockTypesChecker());
   addAstVisitor(new ast::visitor::TypeMatch());
   addAstVisitor(new ast::visitor::CheckValidity());
   addAstVisitor(new ast::visitor::FindEntryPoint());

   addStVisitor(new st::visitor::DepBuilder());

   st::Util::setupBool(this->symbols, this->symbols.gCoreTypes());
   st::Util::setupInts(this->symbols, this->symbols.gCoreTypes());
   st::Util::setupVoid(this->symbols, this->symbols.gCoreTypes());
}

Compiler::~Compiler ()
{
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
   logger.sLevel(log::WARNING);

   opt::Parser opt_parser;
   opt_parser.parse(argc, argv, &logger, gOptions());

   logger.sLevel(gOptions()->getInt("log.level"));

   if (opt_parser._params.size() >= 1)
   {
      _parse_queue.push(opt_parser._params[0]);

      processParseQueue();

      runAstVisitors();
      runStVisitors();

      if (isBuildSuccessful()) emitCode();


      reset_lexer(); // Cleans up lexer global vars

      if (gOptions()->isSet("ast.dump.file")) dumpAst();
      dumpSt();

      printBuildSummary();
   }
}

void
Compiler::dumpAst ()
{
   std::ofstream dump_file;
   dump_file.open(gOptions()->getStr("ast.dump.file").c_str());

   mem::ast::dumper::XmlDumper dumper;
   dumper.dump_to(&ast, dump_file);

   dump_file.close();
   logger.debug("AST dumped to %s", gOptions()->getStr("ast.dump.file").c_str());
}

void
Compiler::dumpSt ()
{
   if (gOptions()->isSet("st.dump.xml"))
   {
      // Open dump file
      // TODO We should have a default output file in case the user did not
      // give one
      std::ofstream st_dump_file(gOptions()->getStr("st.dump.xml").c_str());

      st::visitor::IDumper* dumper = new st::visitor::XmlDumper;
      dumper->_out = &st_dump_file;
      dumper->setup();
      dumper->visitPreorder(symbols._root);

      st_dump_file.close();
      logger.debug("SymbolTable dumped to %s (XML)",
         gOptions()->getStr("st.dump.xml").c_str());
   }
}

void
Compiler::emitCode ()
{
   if (gOptions()->isSet("codegen.llvm-bc"))
   {
      mem::codegen::llvm_::Codegen cg;
      cg._st = &symbols;
      cg.gen(&ast);

      std::ofstream bc_file;
      bc_file.open(gOptions()->getStr("codegen.llvm-bc").c_str());
      bc_file << cg.getLlvmByteCode();
      bc_file.close();

      logger.debug("LLVM ByteCode dumped to %s",
         gOptions()->getStr("codegen.llvm-bc").c_str());
   }
}

void
Compiler::parse (std::string file_path)
{
   this->logger.debug("[%s] parsing...", file_path.c_str());

   // @TODO Split it
   st::Namespace* file_sym = st::Util::createNamespace(this->symbols._root, Util::split(Util::stripFileExtension(file_path),'/'));
   assert(file_sym != NULL);

   reset_lexer();
   std::vector<std::string> paths_tried;
   std::string include_path("");

   // Try finding the file using include path directories
   // TODO This should be moved to fs::FileManager
   fs::File* file = this->fm.openFile(file_path);
   paths_tried.push_back(file_path);
   if (file == NULL)
   {
      std::vector<std::string>::size_type i;
      std::string try_file_path;
      for (i=0; file==NULL && i<this->fm._path.size(); ++i)
      {
         try_file_path.assign(this->fm._path[i] + "/" + file_path);
         file = this->fm.openFile(try_file_path);
         paths_tried.push_back(try_file_path);
         if (file != NULL)
         {
            include_path = this->fm._path[i];
         }
      }
      if (file != NULL)
      {
         file_path.assign(try_file_path);
      }
   }

   if (file != NULL)
   {
      std::string ns(file_path.substr(include_path.length(), file_path.length() - include_path.length() + 1));
      mem::Util::path_to_namespace(ns);
      ast::node::File* file_node = new ast::node::File();
      file_node->sBoundSymbol(file_sym);
      file_node->_id.assign(ns);
      file_node->_include_path.assign(include_path);
      file_node->_path = file_path;
      ast.pushChild(file_node);

      // Used by yyparse
      yyin = fopen(file_path.c_str(), "rb");
      // TODO The file was opened ms before
      // We could open the file only once if we used Bison++
      assert(yyin != NULL);
      yyfile = file;
      yyparse(this->fm, file_node, this->symbols, this->logger, file);

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
            this->logger.log(&warn);
         }
         else
         {
            std::string rel_file_path (find_use._uses[i]);
            mem::Util::namespace_to_path(rel_file_path);
            rel_file_path += ".mem";
            this->_parse_queue.push(rel_file_path);
         }
      }
      fclose(yyin);
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
      this->logger.log(msg);
   }
}

void
Compiler::printBuildSummary ()
{
   std::ostringstream sum;
   if (this->logger._n_fatal_errors > 0)
   {
      sum << this->logger._n_fatal_errors;
      sum << " fatal errors, ";
   }
   if (this->logger._n_errors > 0)
   {
      sum << this->logger._n_errors;
      sum << " errors, ";
   }

   if (this->logger._n_warnings > 0)
   {
      sum << this->logger._n_warnings;
      sum << " warnings, ";
   }

   if (this->isBuildSuccessful())
   {
      this->logger.info("Build SUCCESSFUL", "");
   }
   else
   {
      this->logger.info(sum.str().c_str(), "");
      this->logger.fatalError("Build FAILED", "");
   }
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
      i < ast_visitors.size() && logger._n_fatal_errors == 0; ++i)
   {
      logger.debug("[%s] running...", ast_visitors[i]->_name.c_str());
      ast_visitors[i]->setup(&symbols, &logger);
      ast_visitors[i]->visit_preorder(&ast);
      ast_visitors[i]->tearDown();
   }
}

void
Compiler::runStVisitors ()
{
   for (size_t i = 0; i < st_visitors.size(); ++i)
   {
      logger.debug("[%s] running...", st_visitors[i]->gNameCstr());
      st_visitors[i]->setup();
      st_visitors[i]->visitPreorder(symbols.gRoot());
      st_visitors[i]->tearDown();
   }
}

void
Compiler::setUpOptions ()
{
   _opts.addStrOpt("ast.dump.file");
   _opts.addBoolOpt("codegen.native");
   _opts.addStrOpt("codegen.llvm-bc");
   _opts.addIntEnumOpt("log.level")
      ->bind("unknown", log::UNKNOWN)
      ->bind("debug", log::DEBUG)
      ->bind("info", log::INFO)
      ->bind("warning", log::WARNING)
      ->bind("error", log::ERROR)
      ->bind("fatal-error", log::FATAL_ERROR);
   _opts.addStrOpt("st.dump.xml");


   // Set CLI options
   _opts.addCliOpt ("emit-llvm-bc", "codegen.llvm-bc", "Emit LLVM bytecode");
}

}
