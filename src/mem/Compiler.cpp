#include "mem/Compiler.hpp"


namespace mem {


Compiler::Compiler ()
{
   this->logger._formatter = new log::ConsoleFormatter();
   this->ast._type = MEM_NODE_ROOT;
   this->symbols.setup ();

   this->registerAstVisitor(new ast::visitor::Prechecker());
   this->registerAstVisitor(new ast::visitor::FindClasses());
   this->registerAstVisitor(new ast::visitor::TopTypesChecker());
   this->registerAstVisitor(new ast::visitor::VariableTypesChecker());
   this->registerAstVisitor(new ast::visitor::BlockTypesChecker());
   this->registerAstVisitor(new ast::visitor::TypeMatch());
}

Compiler::~Compiler ()
{
   for (int i = 0 ; i < this->ast_visitors.size() ; ++i)
   {
      assert(this->ast_visitors[i] != NULL);
      delete this->ast_visitors[i];
   }
}

void
Compiler::compile (char* fp)
{
   std::string file_path(fp);
   this->_parse_queue.push(file_path);
   this->processParseQueue();

   for (int i=0; i < this->ast_visitors.size(); ++i)
   {
      this->logger.debug("Running visitor <%s>",this->ast_visitors[i]->_name.c_str());
      this->ast_visitors[i]->init(&this->symbols, &this->logger);
      this->ast_visitors[i]->visit_preorder(&this->ast);
   }

   reset_lexer(); // Cleans up lexer global vars
}

void
Compiler::parse (std::string file_path)
{
   this->logger.info("Parsing {path:%s}...", file_path.c_str());
   reset_lexer();
   std::vector<std::string> paths_tried;
   std::string include_path("");

   // Try finding the file using include path directories
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
      file_node->_id.assign(ns);
      file_node->_include_path.assign(include_path);
      file_node->_path = file_path;
      this->ast.pushChild(file_node);

      // Used by yyparse
      yyin = fopen(file_path.c_str(), "rb");
      // @FIXME The file was opened ms before
      // We could open the file only once if we used Bison++
      ASSERT_NOT_NULL(yyin);
      yyfile = file;
      yyparse(this->fm, file_node, this->symbols, this->logger, file);

      ast::visitor::FindUse find_use;
      find_use.visit_preorder(file_node);
      for (size_t i = 0 ; i < find_use._uses.size() ; ++i)
      {
         if (ns == find_use._uses[i])
         {
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
Compiler::processParseQueue ()
{
   while (!this->_parse_queue.empty())
   {
      this->parse(this->_parse_queue.front());
      this->_parse_queue.pop();
   }
}


void
Compiler::registerAstVisitor (ast::visitor::Visitor* visitor)
{
   this->ast_visitors.push_back(visitor);
}

}
