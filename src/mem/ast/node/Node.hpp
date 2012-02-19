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

   public: inline st::Symbol* gBoundSymbol () {return this->_bound_type;}
   public: inline void sBoundSymbol (st::Symbol* sym) {this->_bound_type = sym;}
   public: inline st::Type* gExprType () {return static_cast<st::Type*>(this->_exp_type);}
   public: inline void sExprType (st::Symbol* sym) {this->_exp_type = sym;};

   public: fs::position::Range* copy_position() { return this->_position->copy_range();}
   public: void eat (Node* n);
   public: static const char* get_type_name (unsigned int type);
   public: Node* getChild (unsigned int i);
   public: bool hasChildren () { return this->_child_count > 0; }
   public: bool isText ();
   public: inline bool isType (unsigned int type) { return this->_type == type; }
   public: void pushChild (Node*);

   public: inline void pushChildren (Node* n1, Node* n2)
   {
      this->pushChild(n1);
      this->pushChild(n2);
   }

   public: inline void pushChildren (Node* n1, Node* n2, Node* n3)
   {
      this->pushChild(n1);
      this->pushChild(n2);
      this->pushChild(n3);
   }

   public: void sDepth (unsigned long depth);
   public: inline fs::position::Range* gPosition() {return this->_position;}
   public: void sPosition(fs::position::Range* pos);
   public: void unlink ();
};


} } }

#endif
