#ifndef _MEM__AST__NODE__NODE__HPP
#define _MEM__AST__NODE__NODE__HPP


#include <stdio.h>
#include "check.h"
#include "macro.h"
#include "mem/fs/position/Range.hpp"
#include "mem/parser/NodeTypes.hpp"
#include "mem/st/Class.hpp"


namespace mem { namespace ast { namespace node {


class Node
{
   public: bool _accept_children;
   public: unsigned long _depth;
   public: unsigned int _child_count;
   public: st::Symbol* _bound_type;
   public: long _expected_child_count;
   public: Node* _first_child;
   public: Node* _last_child;
   public: Node* _next;
   public: Node* _parent;
   public: fs::position::Range* _position;
   public: Node* _prev;
   public: unsigned int _type;
   public: st::Symbol* _exp_type;

   public: Node ();
   public: Node (unsigned int type);
   public: virtual ~Node();

   public: inline void assert_type (unsigned int type)
   {
      if (this->_type != type)
      {
         printf("Node[type:%s] @x%X is not of type %s\n",
            Node::get_type_name(this->_type),
            (unsigned int)this,
            Node::get_type_name(type));
         assert(false);
      }
   }

   public: inline st::Symbol* g_bound_symbol () {return this->_bound_type;}
   public: inline void s_bound_symbol (st::Symbol* sym) {this->_bound_type = sym;}
   public: inline st::Type* g_expr_type () {return static_cast<st::Type*>(this->_exp_type);}
   public: inline void s_expr_type (st::Symbol* sym) {this->_exp_type = sym;};

   public: fs::position::Range* copy_position() { return this->_position->copy_range();}
   public: void eat (Node* n);
   public: static const char* get_type_name (unsigned int type);
   public: Node* get_child (unsigned int i);
   public: bool has_children ()
   {
      return this->_child_count > 0;
   }

   public: bool is_text ();
   public: inline bool is_type (unsigned int type)
   {
      return this->_type == type;
   }
   public: void push_child (Node*);

   public: inline void push_children (Node* n1, Node* n2)
   {
      this->push_child(n1);
      this->push_child(n2);
   }

   public: inline void push_children (Node* n1, Node* n2, Node* n3)
   {
      this->push_child(n1);
      this->push_child(n2);
      this->push_child(n3);
   }

   public: void set_depth (unsigned long depth);
   public: void set_position(fs::position::Range* pos);
   public: void unlink ();
};


} } }

#endif
