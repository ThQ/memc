#ifndef _MEM__ST__SYMBOL__HPP_
#define _MEM__ST__SYMBOL__HPP_


#include <assert.h>
#include <map>
#include <sstream>
#include <stdio.h>
#include <string>
#include "mem/Metadata.hpp"
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
   public: SymbolKind _kind;


   public: Symbol* _parent;
   public: fs::position::Range _pos;
   public: unsigned int _depth;

   // -------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   // -------------------------------------------------------------------------
   public:

   // ---------------------
   // PROPERTY : ChildCount
   // ---------------------
   size_t _child_count;

   inline size_t
   gChildCount() const {return _child_count;}

   virtual st::Symbol*
   gExprType ();

   // --------------
   // PROPERTY : Md
   // -------------
   Metadata* _md;

   inline Metadata*
   gMd() const {return _md;}

   inline void
   sMd (Metadata* md) {_md = md;}

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
   virtual bool
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
   is (SymbolKind kind) const {return _kind == kind;};

   inline bool
   isClassSymbol() const {return is(st::CLASS);}

   inline bool
   isFuncSymbol() const {return is(st::FUNCTION);}

   inline bool
   isPrimitiveSymbol() const {return is(st::PRIMITIVE);}

   inline bool
   isPtrSymbol() const {return is(st::POINTER);}

   inline bool
   isVarSymbol() const {return is(st::VAR);}

   bool
   isAnyTypeSymbol() const;

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
