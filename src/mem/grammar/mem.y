%parse-param{mem::fs::FileManager& fm}
%parse-param{mem::ast::node::Node* ast}
%parse-param{mem::st::SymbolTable& symbols}
%parse-param{mem::log::Logger& logger}
%parse-param{mem::fs::File* file}

%code requires{
#define PASS (0);
#include <stdio.h>
#include <string.h>
#include "mem/ast/node/BinaryExpression.hpp"
#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Field.hpp"
#include "mem/ast/node/LeftUnary.hpp"
#include "mem/ast/node/Primitive.hpp"
#include "mem/ast/node/Root.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Use.hpp"
#include "mem/ast/node/VarDecl.hpp"
#include "mem/fs/File.hpp"
#include "mem/fs/FileManager.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/log/Logger.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/Compiler.hpp"
using namespace mem;

#ifndef YYERROR_VERBOSE
#define YYERROR_VERBOSE 1
#endif

#define YYLTYPE fs::position::Range
#define YYLTYPE_IS_DECLARED 1

#define YYLLOC_DEFAULT(Current, Rhs, N) \
   do \
   { \
      if (YYID (N)) \
      { \
         (Current).s_line(YYRHSLOC (Rhs, 1)._line); \
         (Current).s_line_end(YYRHSLOC (Rhs, 1)._line_end); \
         (Current).s_col_start(YYRHSLOC (Rhs, 1)._column_start); \
         (Current).s_col_end(YYRHSLOC (Rhs, N)._column_end); \
         (Current)._file = YYRHSLOC(Rhs, 1)._file; \
      } \
      else \
      { \
         (Current).s_line(YYRHSLOC (Rhs, 0)._line); \
         (Current).s_line_end(YYRHSLOC (Rhs, 0)._line_end); \
         (Current).s_col_start(YYRHSLOC (Rhs, 0)._column_end); \
         (Current).s_col_end(YYRHSLOC (Rhs, 0)._column_end); \
         (Current)._file = NULL; \
      } \
   } \
   while (YYID (0))
}

%code {
extern int yylex();

void yyerror(fs::FileManager& fm, ast::node::Node* ast, st::SymbolTable& symbols, log::Logger& logger, fs::File* file, const char *s)
{
   fs::position::Position* pos = new fs::position::Position();
   pos->_file = file;

   log::Message* msg = new log::Message(log::ERROR);
   msg->sMessage("Syntax error");
   msg->sDescription(s);
   msg->sPosition(pos);
   logger.log(msg);
}
}


%code requires {
}

%union {
   int integer;
   char* text;
   ast::node::Node* binary_node;
   ast::node::Node* node;
   ast::node::Text* text_node;
}

%code {
}


%locations
%token T_AROBASE
%token T_CLASS
%token T_COMMA
%token T_CP
%token T_DEDENT
%token T_DOT
%token T_ELSE
%token T_EQ
%token T_IF
%token <text> T_ID
%token T_INDENT
%token T_INTERFACE
%token T_LBRACKET
%token T_LITERAL_FLOAT
%token T_LITERAL_HEX
%token <text> T_LITERAL_INT
%token T_NEW
%token T_NEWLINE
%token T_OP
%token T_PASS
%token T_PATCH
%token T_PRIMITIVE
%token T_OBJECT
%token T_RBRACKET
%token T_RARR
%token <text> T_STRING
%token T_USE
%token T_WHITESPACE
%token T_LEFT_BINARY_OP
%token T_RETURN
%token T_SEMICOLON
%token T_WHILE
%token T_SELF

%right <node> T_OP T_CP
%right <node> T_BANG
%left <node> T_EQ_EQ T_GT T_RARR_EQ T_LT T_RARR T_LARR_EQ
%left <node> T_MINUS T_PLUS
%left <node> T_MUL T_DIV
%left <node> T_DOT
%left <node> T_MUL_MUL T_MODULO
%left <node> T_MINUS_MINUS T_PLUS_PLUS

%type <node> binary_expr
%type <text_node> binary_operator
%type <node> block
%type <node> call
%type <node> class_declaration
%type <node> compound_statement
%type <node> dot_expr
%type <node> expr
%type <node> expr_list
%type <node> function_declaration
%type <node> function_declaration_parameter
%type <node> function_declaration_parameter_list
%type <text> function_name
%type <text_node> id
%type <node> if
%type <text_node> left_unary_expr
%type <text_node> left_unary_operator
%type <text_node> literal
%type <node> member_declaration
%type <node> return_statement
%type <node> simple_statement
%type <node> statement
%type <node> statements
%type <node> top_level_statement
%type <node> top_level_statements
%type <node> type_block
%type <node> type_declaration
%type <node> type_name
%type <text_node> use
%type <node> variable_declaration
%type <node> while
%type <binary_node> qualified_id

%%

input :
   /* empty */
   | input T_NEWLINE
   | input T_DEDENT
   | input T_WHITESPACE T_NEWLINE
   | input use
   {
      ast->pushChild($2);
   }
   | input type_declaration
   {
      ast->pushChild($2);
   }


use:
   T_USE T_ID T_NEWLINE
   {
      $$ = new ast::node::Use();
      $$->sValue($2, strlen($2));
      $$->sPosition(new fs::position::Range(@1, @3));
      free($2);
   }
/*
=============================================================================
  DECLARATION
=============================================================================
*/

type_block:
   T_NEWLINE T_INDENT top_level_statements T_DEDENT
   {
      $$ = new ast::node::Block();
      $$->eat($3);
      delete $3;
   }

type_declaration:
   class_declaration

class_declaration:
   T_CLASS id type_block
   {
      ast::node::Class* cls = new ast::node::Class();

      cls->sValue($2->_value);
      cls->eat($3);
      cls->sPosition(new fs::position::Range(@1, @3));
      delete $2;
      delete $3;
      $$ = cls;
   }
   | T_CLASS id T_LT id type_block
   {
      ast::node::Class* cls = new ast::node::Class();

      cls->sValue($2->_value);
      cls->eat($5);
      cls->pushChild($4);
      cls->sPosition(new fs::position::Range(@1, @3));
      delete $2;
      delete $5;
      $$ = cls;
   }


/*
=============================================================================
  CONTROL FLOW
=============================================================================
*/
if:
   T_IF expr block
   {
      $$ = new ast::node::Node(MEM_NODE_IF);
      $$->pushChildren($2, $3);
      $$->sPosition(new fs::position::Range(@1, @2));
   }
   | T_IF expr block T_ELSE block
   {
      $$ = new ast::node::Node(MEM_NODE_IF_ELSE);
      $$->pushChildren($2, $3, $5);
      $$->sPosition(new fs::position::Range(@1, @5));
   }

while:
   T_WHILE expr block
   {
      $$ = new ast::node::Node(MEM_NODE_WHILE);
      $$->pushChildren($2, $3);
      $$->sPosition(new fs::position::Range(@1, @3));
   }

block:
   T_NEWLINE T_INDENT statements T_DEDENT
   {
      $$ = new ast::node::Block();
      $$->sPosition(new fs::position::Range(@3, @3));
      $$->eat($3);
      delete $3;
   }

statements:
   statement
   {
      $$ = new ast::node::Node();
      $$->pushChild($1);
   }
   | statements statement
   {
      if ($$ == 0)
      {
         $$ = new ast::node::Node();
      }
      $$->pushChild($2);
   }

statement:
   expr T_NEWLINE
   {
      $$ = $1;
   }
   | simple_statement
   {
      $$ = $1;
   }
   | compound_statement
   {
      $$ = $1;
   }

compound_statement:
   if
   | while

simple_statement:
   variable_declaration
   | return_statement

return_statement:
   T_RETURN expr
   {
      $$ = new ast::node::Node(MEM_NODE_RETURN);
      $$->pushChild($2);
   }

top_level_statement:
   member_declaration
   | function_declaration
   | T_PASS T_NEWLINE
   {
      $$ = NULL;
   }

top_level_statements:
   top_level_statement
   {
      $$ = new ast::node::Node();
      $$->pushChild($1);
   }
   | top_level_statements top_level_statement
   {
      $$->pushChild($2);
   }

function_name:
   T_ID
   | T_STRING

function_declaration:
   // Virtual function : no parameters, return type
   // Ex: my_function_name() :my_return_type
   function_name T_OP T_CP T_RARR type_name T_NEWLINE
   {
      ast::node::Function* n = new ast::node::Function();
      n->sValue($1, strlen($1));
      n->pushChild($5);
      n->sPosition(@$.copy_range());
      $$ = (ast::node::Node*)n;

      free($1);
   }
   // Virtual function : parameters, return type
   // Ex: my_function_name(my_variable :my_type) :my_return_type
   | function_name T_OP function_declaration_parameter_list T_CP T_RARR type_name T_NEWLINE
   {
      $3->sPosition(new fs::position::Range(
         *($3->getChild(0)->_position),
         *($3->getChild($3->_child_count-1)->_position)));

      ast::node::Function* n = new ast::node::Function();
      n->sValue($1, strlen($1));
      n->pushChildren($3, $6);
      n->sPosition(@$.copy_range());
      $$ = (ast::node::Node*)n;

      free($1);
   }
   // Ex: my_function_name() :my_return_type
   | function_name T_OP T_CP T_RARR type_name block
   {
      ast::node::Function* n = new ast::node::Function();
      n->sValue($1, strlen($1));
      n->pushChildren($5, $6);
      n->sPosition(@$.copy_range());
      $$ = (ast::node::Node*)n;

      free($1);
   }
   // Ex: my_function_name(my_variable :my_type) :my_return_type
   | function_name T_OP function_declaration_parameter_list T_CP T_RARR type_name block
   {
      $3->sPosition(new fs::position::Range(
         *($3->getChild(0)->_position),
         *($3->getChild($3->_child_count-1)->_position)));
      ast::node::Function* n = new ast::node::Function();
      n->sValue($1, strlen($1));
      n->pushChildren($3, $6, $7);
      n->sPosition(@$.copy_range());
      $$ = (ast::node::Node*)n;

      free($1);
   }

member_declaration:
   // Ex: my_variable :my_type
   id T_SEMICOLON type_name T_NEWLINE
   {
      ast::node::Field* field = new ast::node::Field();
      field->sPosition(@$.copy_range());
      field->pushChildren($1, $3);

      $$ = (ast::node::Node*)field;
   }

function_declaration_parameter_list:
   function_declaration_parameter
   {
      $$ = new ast::node::Node(MEM_NODE_FUNCTION_PARAMETERS);
      $$->pushChild($1);
   }
   | function_declaration_parameter_list T_COMMA function_declaration_parameter
   {
      $$->pushChild($3);
   }

function_declaration_parameter:
   id T_SEMICOLON type_name
   {
      $$ = new ast::node::Node(MEM_NODE_FUNCTION_PARAMETER);
      $$->pushChildren($1, $3);
      $$->sPosition(new fs::position::Range(@1, @3));
   }

type_name :
   qualified_id
   {
      $$ = static_cast<ast::node::Node*>($1);
   }

variable_declaration :
   // Ex: my_variable :my_type
   id T_SEMICOLON type_name T_NEWLINE
   {
      ast::node::VarDecl* n = new ast::node::VarDecl();
      n->sPosition(@$.copy_range());
      n->pushChildren($1, $3);
      $$ = (ast::node::Node*)n;
   }
   // Ex: my_variable := my_function()
   | id T_SEMICOLON T_EQ expr T_NEWLINE
   {
      ast::node::Text* type = new ast::node::Text(MEM_NODE_ID);
      type->sValue("$AUTO");

      ast::node::VarDecl* n = new ast::node::VarDecl();
      n->pushChildren($1, type, $4);
      $$ = (ast::node::Node*)n;
   }
   // Ex: my_variable :my_type = my_function()
   | id T_SEMICOLON type_name T_EQ expr T_NEWLINE
   {
      ast::node::VarDecl* n = new ast::node::VarDecl();
      n->sPosition(@$.copy_range());
      n->pushChildren($1, $3, $5);
      $$ = (ast::node::Node*)n;
   }

id :
   T_ID
   {
      $$ = new ast::node::Text(MEM_NODE_ID);
      $$->sPosition(@$.copy_range());
      $$->sValue($1, strlen($1));

      free($1);
   }

qualified_id :
   id
   {
      $$->_type = MEM_NODE_FINAL_ID;
   }
   | qualified_id T_DOT id
   {
      $$ = new ast::node::Text(MEM_NODE_DOT);
      $$->pushChildren($1, $3);
      $$->sPosition(@$.copy_range());
   }

dot_expr :
   expr T_DOT id
   {
      $$ = new ast::node::Node(MEM_NODE_DOT);
      $$->sPosition(@$.copy_range());
      $$->pushChildren($1, $3);
   }

expr :
   literal
   {
      $$ = $1;
   }
   | dot_expr
   {
      $$ = $1;
   }
   | binary_expr
   {
      $$ = (ast::node::Node*)$1;
   }
   | left_unary_expr
   {
      $$ = (ast::node::Node*)$1;
   }
   /* ex: (1 + 2 + 3) */
   | T_OP expr T_CP
   {
      $$ = new ast::node::Node(MEM_NODE_GROUP);
      $$->pushChild($2);
   }
   | qualified_id
   {
      $$ = static_cast<ast::node::Node*>($1);
   }
   | call
   {
      $$ = (ast::node::Node*)$1;
   }

binary_operator:
   T_DIV
   {
      $$ = new ast::node::Text();
      $$->sValue("__div__", 7);
   }
   | T_EQ_EQ
   {
      $$ = new ast::node::Text();
      $$->sValue("__equals__", 10);
   }
   | T_LT
   {
      $$ = new ast::node::Text();
      $$->sValue("__lt__", 6);
   }
   | T_LARR_EQ
   {
      $$ = new ast::node::Text();
      $$->sValue("__lte__", 7);
   }
   | T_MINUS
   {
      $$ = new ast::node::Text();
      $$->sValue("__minus__", 9);
   }
   | T_MODULO
   {
      $$ = new ast::node::Text();
      $$->sValue("__modulo__", 10);
   }
   | T_MUL
   {
      $$ = new ast::node::Text();
      $$->sValue("__mul__", 7);
   }
   | T_MUL_MUL
   {
      $$ = new ast::node::Text();
      $$->sValue("__pow__", 7);
   }
   | T_PLUS
   {
      $$ = new ast::node::Text(MEM_NODE_ID);
      $$->sValue("__plus__", 8);
   }
   | T_GT
   {
      $$ = new ast::node::Text();
      $$->sValue("__gt__", 6);
   }
   | T_RARR_EQ
   {
      $$ = new ast::node::Text();
      $$->sValue("__gte__", 7);
   }

left_unary_operator:
   T_BANG
   {
      $$ = new ast::node::Text(MEM_NODE_ID);
      $$->sValue("__bang__");
   }
   | T_MINUS_MINUS
   {
      $$ = new ast::node::Text(MEM_NODE_ID);
      $$->sValue("__minus_minus__");
   }
   | T_PLUS_PLUS
   {
      $$ = new ast::node::Text(MEM_NODE_ID);
      $$->sValue("__plus_plus__");
   }

binary_expr:
   expr binary_operator expr
   {
      ast::node::Node* func = new ast::node::Node(MEM_NODE_DOT);
      func->pushChildren($1, $2);

      $$ = new ast::node::Text(MEM_NODE_CALL);
      $$->pushChildren(func, $3);
   }

left_unary_expr:
   left_unary_operator expr
   {
      ast::node::Node* func = new ast::node::Node(MEM_NODE_DOT);
      func->pushChild ($2);

      $$ = new ast::node::Text(MEM_NODE_CALL);
      $$->pushChild(func);
   }

expr_list :
   expr
   {
      $$ = new ast::node::Node(MEM_NODE_EXPR_LIST);
      $$->pushChild($1);
   }
   | expr_list T_COMMA expr
   {
      if ($$ == 0)
      {
         $$ = new ast::node::Node(MEM_NODE_EXPR_LIST);
      }
      $$->pushChild($3);
   }

call :
   /* ex: my_func() */
   expr T_OP T_CP
   {
      $$ = new ast::node::Node(MEM_NODE_CALL);
      $$->sPosition(new fs::position::Range(@1, @3));
      $$->pushChild($1);
   }
   /* ex: my_func(1, 2, 3) */
   | expr T_OP expr_list T_CP
   {
      $3->sPosition(@3.copy_range());
      $$ = new ast::node::Node(MEM_NODE_CALL);
      $$->sPosition(new fs::position::Range(@1, @4));
      $$->pushChildren($1, $3);
   }

literal :
   T_LITERAL_INT
   {
      $$ = new ast::node::Text(MEM_NODE_LITERAL_INT);
      $$->sPosition(@1.copy_range());
      $$->sValue($1);

      free($1);
   }
%%

#include "mem/ast/node/Node.hpp"
