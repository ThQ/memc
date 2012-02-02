#include "mem/Compiler.hpp"

namespace mem {


Compiler::Compiler ()
{
   this->logger._formatter = new log::ConsoleFormatter();
}

Compiler::~Compiler ()
{
}

void
Compiler::compile (char* fp)
{
   std::string file_path(fp);
   this->_parse_queue.push(file_path);
   this->process_parse_queue();

   // Find types and register them in the symbol table
   ast::visitor::FindClasses find_classes(&this->symbols);
   this->logger.info("Starting [FindClasses] visitor...%s", "");
   find_classes.visit_preorder(this->ast._root);

   // Check if top types used exist
   ast::visitor::TopTypesChecker check_top_types(&this->symbols, &this->logger);
   this->logger.info("Starting [TopTypesChecker] visitor...%s", "");
   check_top_types.visit_preorder(this->ast._root);

   // Check if types in variable declarations exist
   ast::visitor::VariableTypesChecker check_variable_declaration_types(&this->symbols, &this->logger);
   this->logger.info("Starting [VariableTypesChecker] visitor...%s", "");
   check_variable_declaration_types.visit_preorder(this->ast._root);

   // Check types in blocks
   ast::visitor::BlockTypesChecker check_block_types(&this->symbols, &this->logger);
   this->logger.info("Starting [BlockTypesChecker] visitor...%s", "");
   check_block_types.visit_preorder(this->ast._root);

   // Check type matches (in variable declarations, etc)
   ast::visitor::TypeMatch type_match(&this->symbols, &this->logger);
   type_match.visit_preorder(this->ast._root);

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
   fs::File* file = this->fm.open_file(file_path);
   paths_tried.push_back(file_path);
   if (file == NULL)
   {
      std::vector<std::string>::size_type i;
      std::string try_file_path;
      for (i=0; file==NULL && i<this->fm._path.size(); ++i)
      {
         try_file_path.assign(this->fm._path[i] + "/" + file_path);
         file = this->fm.open_file(try_file_path);
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
      this->ast._root->push_child(file_node);

      // Used by yyparse
      yyin = fopen(file_path.c_str(), "rb");
      // @FIXME The file was opened ms before
      // We could open the file only once if you used Bison++
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
            warn.format_message(
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

      log::Message msg(log::ERROR);
      msg.format_message("Couldn't open file {path:%s}.", file_path.c_str());
      msg.set_description(description);
      this->logger.log(&msg);
   }
}

void
Compiler::process_parse_queue ()
{
   while (!this->_parse_queue.empty())
   {
      this->parse(this->_parse_queue.front());
      this->_parse_queue.pop();
   }
}


}
