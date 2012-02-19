#ifndef _MEM__ST__SYMBOL__HPP_
#define _MEM__ST__SYMBOL__HPP_


#include <assert.h>
#include <map>
#include <sstream>
#include <stdio.h>
#include <string>
#include "mem/fs/position/Range.hpp"
#include "mem/st/SymbolKind.hpp"


namespace mem { namespace st {


class Symbol
{
   public: std::map<std::string, Symbol*> _children;
   public: unsigned int _child_count;
   public: Symbol* _first_child;
   public: SymbolKind _kind;
   public: Symbol* _last_child;
   public: std::string _name;

   public: inline std::string gName() {return this->_name;}
   public: inline const char* gNameCstr() {return this->_name.c_str();}

   public: Symbol* _parent;
   public: Symbol* _prev;
   public: Symbol* _next;
   public: fs::position::Range _pos;
   public: unsigned int _depth;

   public: Symbol ();
   public: virtual ~Symbol ();
   public: bool addChild (Symbol* symb);
   public: bool is (SymbolKind kind);
   public: Symbol* getChild (std::string name);
   public: virtual std::string gQualifiedName();
   public: const char* gQualifiedNameCstr() { return this->gQualifiedName().c_str();}
   //public: virtual void print ();
   //public: void print_depth ();
   public: void sName (char* name, size_t len);
   public: void sName (std::string name);
};


} }

#endif
