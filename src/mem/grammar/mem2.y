%{
#define PASS (0);
#include <stdio.h>
#define DEBUG(args ...) printf(args);

extern int yylex();

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
}

%token T_CLASS
%token T_COMMA
%token T_DEF
%token T_DOT
%token T_EOL
%token <text> T_ID
%token <integer> T_LITERAL_INT
%token T_LITERAL_FLOAT
%token T_LITERAL_HEX
%token T_NAMESPACE
%token T_NEW
%token T_PASS
%token T_OP_DECORATOR
%token T_OP_TYPE
%token T_USE
%token T_WHITESPACE

%left T_OP
%left T_CP
%left T_PLUS
%right T_OP_EQUAL

%%

input :
   /* empty */
   | input opt_space T_PASS line_end
   | input use line_end
   | input namespace line_end
   | input class line_end
   | input opt_space decorator line_end
   | input opt_space function_def line_end
   | input opt_space var_decl line_end
   | input opt_space call line_end
   | input line_end

namespace :
   T_NAMESPACE T_WHITESPACE T_ID
   {
      mem::parser::NamespaceNode* n = new mem::parser::NamespaceNode();
      n->_value = $3;
      ast->push_node(n);
   }

class_raw :
   T_CLASS T_WHITESPACE T_ID
   {
      mem::parser::ClassNode* n = new mem::parser::ClassNode();
      n->_value = $3;
      ast->push_node(n);
   }

class :
   class_raw
   | T_WHITESPACE class_raw

function_def :
   T_DEF T_WHITESPACE T_ID opt_space T_OP opt_space T_CP
   {
      mem::parser::FuncNode* n = new mem::parser::FuncNode();
      n->_value = $3;
      ast->push_node(n);
   }

use :
   T_USE T_WHITESPACE T_ID
   {
      mem::parser::UseNode* n = new mem::parser::UseNode();
      n->_value = $3;
      ast->push_node(n);
   }

new :
   T_NEW T_WHITESPACE T_ID opt_space call_parameters
   {
      mem::parser::NewObjNode* n = new mem::parser::NewObjNode();
      n->_value = $3;
      ast->push_node(n);
   }

decorator :
   T_OP_DECORATOR T_ID
   {
      mem::parser::DecoratorNode* n = new mem::parser::DecoratorNode();
      n->_value = $2;
      ast->push_node(n);
   }

eval :
   literal
   | call
   | add
   | new

eval_list :
   eval
   | eval opt_space T_COMMA opt_space eval_list

opt_eval_list :
   /* empty */
   | eval_list

call :
   obj_call
   | literal_call
   | func_call

call_parameters :
   T_OP opt_space opt_eval_list opt_space T_CP

obj_call :
   T_ID T_DOT func_call
   {
      DEBUG("[OBJECT_CALL|object_name=%s]\n", $1);
   }

add :
   eval T_WHITESPACE T_PLUS T_WHITESPACE eval
   {
      DEBUG("[ADD]\n");
      mem::parser::AddNode* n = new mem::parser::AddNode();
      ast->push_node(n);
   }

func_call :
   T_ID opt_space call_parameters
   {
      DEBUG("[FUNC_CALL|name=%s]\n", $1);
      mem::parser::CallNode* n = new mem::parser::CallNode();
      n->_value = $1;
      ast->push_node(n);
   }

literal_call :
   literal T_DOT func_call

var_decl :
   /* str1 :string = "string" */
   T_ID opt_space T_OP_TYPE T_ID opt_space T_OP_EQUAL opt_space eval
   {
      mem::parser::VarDeclNode* n = new mem::parser::VarDeclNode();
      n->_value = $1;
      ast->push_node(n);
   }
   /* str1 := "string" */
   | T_ID opt_space T_OP_TYPE opt_space T_OP_EQUAL opt_space eval
   {
      mem::parser::VarDeclNode* n = new mem::parser::VarDeclNode();
      n->_value = $1;
      ast->push_node(n);
   }
   /* str1 :string */
   | T_ID opt_space T_OP_TYPE T_ID
   {
      mem::parser::VarDeclNode* n = new mem::parser::VarDeclNode();
      n->_accept_children = false;
      n->_value = $1;
      ast->push_node(n);
   }

literal :
   T_LITERAL_INT
   {
      mem::parser::IntNode* n = new mem::parser::IntNode();
      n->_value = $1;
      ast->push_node(n);
   }
   | T_LITERAL_FLOAT
   | T_LITERAL_HEX


line_end :
   T_WHITESPACE eol
   | eol
   | /* empty */

eol :
   T_EOL
   {
      ast->push_eol();
   }

opt_space :
   T_WHITESPACE
   | /* empty */

%%

#include "mem/parser/Node.hpp"
