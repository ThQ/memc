#ifndef _MEM_AST_AST_HPP_
#define _MEM_AST_AST_HPP_


#include "macro.h"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Root.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast {


class Ast
{
   public: node::Root* _root;
   public: node::Node* _current;

   public: Ast ();
   public: ~Ast ();

   public: void dump ();
   public: void push_node (node::Node* n);
   public: void reset ();
};


} }

#endif
