%{
#define PASS (0);
#include <stdio.h>
#include <string.h>
#define DEBUG(args ...) printf(args);

#ifndef YYERROR_VERBOSE
#define YYERROR_VERBOSE 1
#endif

extern int yylex();

int yyerror(char *s)
{
   printf("%s\n",s);
   return(0);
}


%}

%code requires {
#include "mem/parser/Ast.hpp"
extern mem::parser::Ast* ast;
}

%code {
#ifndef _AST_DEFINED
#define _AST_DEFINED
mem::parser::Ast* ast = new mem::parser::Ast();
#endif
}

%union{
   int integer;
   char* text;
   mem::parser::Node* node;
   mem::parser::TextNode* text_node;
}

%token T_CLASS
%token T_COMMA
%token T_DEF
%token T_DOT
%token T_EOL
%token <text> T_ID
%token <text> T_LITERAL_INT
%token T_LITERAL_FLOAT
%token T_LITERAL_HEX
%token T_NAMESPACE
%token T_NEW
%token T_PASS
%token T_OP_DECORATOR
%token T_OP_TYPE
%token T_USE
%token T_WHITESPACE
%token T_LEFT_BINARY_OP
%token T_SEMICOLON
%token T_EQ

%left T_OP
%left T_CP
%right T_LEFT_BINARY_OP

%type <text_node> use
%type <text_node> namespace_decl
%type <text_node> class_decl
%type <node> class_declarations
%type <text_node> function_decl
%type <node> function_declarations
%type <text_node> literal
%type <node> eval
%type <node> eval_list
%type <node> statements
%type <node> statement
%type <node> var_decl
%type <text_node> call


%%

input :
   /* empty */
   | line_end
   | input line_end
   | input use
   {
      ast->_root->push_child($2);
   }
   | input class_declarations
   {
      ast->_root->push_child($2);
   }

use :
   /* use mem.logging */
   T_USE T_WHITESPACE T_ID line_end
   {
      $$ = new mem::parser::TextNode();
      $$->_type = MEM_NODE_USE;
      $$->_value = $3;
      $$->_len = strlen($3);
   }

namespace_decl :
   /* namespace my_namespace */
   T_NAMESPACE T_WHITESPACE T_ID line_end
   {
      $$ = new mem::parser::TextNode();
      $$->_type = MEM_NODE_NAMESPACE;
      $$->_value = $3;
      $$->_len = strlen($3);
   }
   | T_NAMESPACE T_WHITESPACE T_ID line_end class_declarations
   {
      $$ = new mem::parser::TextNode();
      $$->_type = MEM_NODE_NAMESPACE;
      $$->_value = $3;
      $$->_len = strlen($3);
      $$->eat($5);
   }

class_declarations :
   class_decl
   {
      $$ = new mem::parser::Node();
      $$->push_child($1);
   }
   | class_declarations class_decl
   {
      if ($$ == 0)
      {
         $$ = new mem::parser::Node();
      }
      $$->eat($2);
   }

class_decl :
   /* class MyClass */
   opt_space T_CLASS T_WHITESPACE T_ID line_end
   {
      $$ = new mem::parser::TextNode();
      $$->_type = MEM_NODE_CLASS;
      $$->_value = $4;
      $$->_len = strlen($4);
   }
   | opt_space T_CLASS T_WHITESPACE T_ID line_end function_decl
   {
      $$ = new mem::parser::TextNode();
      $$->_type = MEM_NODE_CLASS;
      $$->_value = $4;
      $$->_len = strlen($4);
      $$->push_child($6);
   }

decorator :
   /* @static */
   T_OP_DECORATOR T_ID line_end
   {
      mem::parser::DecoratorNode* n = new mem::parser::DecoratorNode();
      n->_value = $2;
      ast->push_node(n);
   }

function_declarations:
   function_decl
   {
      $$ = new mem::parser::Node();
      $$->push_child($1);
   }
   | function_declarations function_decl
   {
      if ($$ == 0)
      {
         $$ = new mem::parser::Node();
      }
      $$->push_child($2);
   }

function_decl:
   /* my_function () */
   opt_space T_ID opt_space T_OP opt_space T_CP line_end statements
   {
      $$ = new mem::parser::TextNode();
      $$->_type = MEM_NODE_FUNCTION;
      $$->_value = $2;
      $$->_len = strlen($2);
      $$->eat($8);
   }

statements:
   statement
   {
      $$ = new mem::parser::Node();
      $$->push_child($1);
   }
   | statements statement
   {
      if ($$ == 0)
      {
         $$ = new mem::parser::Node();
      }
      $$->push_child($2);
   }

statement:
   opt_space eval line_end
   {
      $$ = $2;
   }

eval :
   /* ex: 1 + 1 */
   eval opt_space T_LEFT_BINARY_OP opt_space eval
   {
      mem::parser::Node* n = new mem::parser::Node(MEM_NODE_BINARY_ADD);
      n->push_child($1);
      n->push_child($5);
      $$ = n;
   }
   | var_decl
   {
      $$ = $1;
   }
   | call
   {
      $$ = $1;
   }
   | T_ID
   {
      mem::parser::TextNode* n = new mem::parser::TextNode();
      n->_type = MEM_NODE_ID;
      n->_value = $1;
      n->_len = strlen($1);
      $$ = n;
   }
   | literal
   {
      $$ = $1;
   }

eval_list :
   eval
   {
      $$ = new mem::parser::Node();
      $$->push_child($1);
   }
   | eval_list opt_space T_COMMA opt_space eval
   {
      if ($$ == 0)
      {
         $$ = new mem::parser::Node();
      }
      $$->push_child($5);
   }

var_decl :
   /* ex: str1 :string */
   T_ID opt_space T_SEMICOLON T_ID
   {
      mem::parser::TextNode* type = new mem::parser::TextNode();
      type->_type = MEM_NODE_ID;
      type->_value = $4;
      type->_len = strlen($4);

      mem::parser::TextNode* var = new mem::parser::TextNode();
      var->_type = MEM_NODE_VARIABLE;
      var->_value = $1;
      var->_len = strlen($1);
      var->push_child(type);
      $$ = var;
   }
   /* ex: int_var :int = 1 */
   | T_ID opt_space T_SEMICOLON T_ID opt_space T_EQ opt_space eval
   {
      mem::parser::TextNode* id = new mem::parser::TextNode();
      id->_type = MEM_NODE_ID;
      id->_value = $4;
      id->_len = strlen($4);

      mem::parser::TextNode* var = new mem::parser::TextNode();
      var->_type = MEM_NODE_VARIABLE;
      var->_value = $1;
      var->_len = strlen($1);
      var->push_child(id);
      var->push_child($8);
      $$ = var;
   }

call :
   /* ex: my_func() */
   T_ID opt_space T_OP opt_space T_CP
   {
      $$ = new mem::parser::TextNode();
      $$->_type = MEM_NODE_CALL;
      $$->_value = $1;
      $$->_len = strlen($1);
   }
   /* ex: my_func(1, 2, 3) */
   | T_ID opt_space T_OP opt_space eval_list T_CP
   {
      $$ = new mem::parser::TextNode();
      $$->_type = MEM_NODE_CALL;
      $$->_value = $1;
      $$->_len = strlen($1);
      $$->eat($5);
   }

literal :
   T_LITERAL_INT
   {
      $$ = new mem::parser::TextNode();
      $$->_type = MEM_NODE_LITERAL_INT;
      $$->_value = $1;
      $$->_len = strlen($1);
   }

line_end :
   eol
   | T_WHITESPACE eol

eol :
   T_EOL
   {
   }

opt_space :
   /* emtpy */
   | T_WHITESPACE

%%

#include "mem/parser/Node.hpp"
