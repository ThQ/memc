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


/**
 * A base class for all symbols stored in the symbol table.
 */
class Symbol
{
   public: typedef std::map<std::string, Symbol*> SymbolCollection;
   public: typedef SymbolCollection::iterator SymbolCollectionIterator;

   public: SymbolCollection _children;
   //public: Symbol* _first_child;
   public: SymbolKind _kind;
   //public: Symbol* _last_child;


   public: Symbol* _parent;
   //public: Symbol* _prev;
   //public: Symbol* _next;
   public: fs::position::Range _pos;
   public: unsigned int _depth;

   // -------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   // -------------------------------------------------------------------------
   public:


   public: size_t _child_count;
   public: inline size_t gChildCount() const {return _child_count;}

   // ---------------
   // PROPERTY : Name
   // ---------------
   std::string _name;
   inline std::string gName() const {return this->_name;}
   inline const char* gNameCstr() const {return this->_name.c_str();}
   void sName (char* name, size_t len);
   void sName (std::string name);

   // ---------------
   // PROPERTY : Size
   // ---------------
   int _size;
   inline int gSize() const {return this->_size;}
   inline void sSize(int size) {this->_size = size;}


   // -------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   // -------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Symbol ();

   /**
    * Destructor.
    */
   virtual
   ~Symbol ();


   // -------------------------------------------------------------------------
   // PUBLIC METHODS
   // -------------------------------------------------------------------------
   public:

   /**
    * Appends a child symbol.
    */
   bool
   addChild (Symbol* symb);

   /**
    * Returns a child given its name.
    */
   virtual Symbol*
   getChild (std::string name);

   /**
    * Returns true if the symbol is of a given kind.
    */
   inline bool
   is (SymbolKind kind) const {return this->_kind == kind;};

   inline bool
   isClassSymbol() const {return this->is(st::CLASS);}

   inline bool
   isFuncSymbol() const {return this->is(st::FUNCTION);}

   inline bool
   isPtrSymbol() const {return this->is(st::POINTER);}

   inline bool
   isVarSymbol() const {return this->is(st::VAR);}

   /**
    * Returns true if the symbol is a type symbol (Type, Class, Primitive, ...).
    */
   bool
   isTypeSymbol () const;

   /**
    * Returns the qualified name of the symbol.
    *
    * If this symbol is named <Socket> and its parent name is <net>, then it
    * will return <net.Socket>
    */
   virtual std::string
   gQualifiedName();

   /**
    * Returns the qualified name as a char pointer.
    */
   inline const char*
   gQualifiedNameCstr() { return this->gQualifiedName().c_str();}
};


} }

#endif
