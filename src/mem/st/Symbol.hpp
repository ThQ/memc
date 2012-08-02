#ifndef _MEM__ST__SYMBOL__HPP_
#define _MEM__ST__SYMBOL__HPP_


#include <assert.h>
#include <map>
#include <sstream>
#include <stdio.h>
#include <string>
#include "mem/Metadata.hpp"
#include "mem/ss.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/st/SymbolKind.hpp"


namespace mem { namespace st {


/**
 * A base class for all symbols stored in the symbol table.
 */
class Symbol
{
   public:
   typedef std::map<std::string, Symbol*> SymbolCollection;
   typedef SymbolCollection::iterator SymbolCollectionIterator;

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   size_t _child_count;
   SymbolCollection _children;
   unsigned int _depth;
   SymbolKind _kind;
   ::mem::Metadata* _md;
   std::string _name;
   Symbol* _parent;
   fs::position::Range _pos;
   int _size;


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ChildCount
   GETTER(ChildCount, size_t) {return _children.size();}

   virtual st::Symbol*
   gExprType ();

   // Children
   GETTER_REF(Children, SymbolCollection) {return _children;}

   // Depth
   GETTER(Depth, int) {return _depth;}
   SETTER(Depth, int) {_depth = val;}

   // Kind
   GETTER(Kind, SymbolKind) {return _kind;}

   // Metadata
   GETTER(Metadata, ::mem::Metadata*) {return _md;}
   SETTER(Metadata, ::mem::Metadata*) {_md = val;}

   // Name
   GETTER(Name, std::string) {return _name;}
   SETTER(Name, std::string) {_name = val;}

   // NameCstr
   GETTER(NameCstr, const char*) {return Name().c_str();}
   //void sName (char* name, size_t len);

   // Parent
   GETTER(Parent, st::Symbol*) {return _parent;}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
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


   //--------------------------------------------------------------------------
   // PUBLIC METHODS
   //--------------------------------------------------------------------------
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

   std::vector<st::Symbol*>
   getParents ();

   void
   hintName (Symbol* parent, std::string hint);

   /**
    * Returns true if the symbol is of a given kind.
    */
   inline bool
   is (SymbolKind kind) const {return _kind == kind;};

   inline bool
   isArgSymbol() const {return is(st::ARG);}

   inline bool
   isAliasSymbol() const {return is(st::ALIAS);}

   inline bool
   isArraySymbol() const {return is(st::ARRAY);}

   inline bool
   isClassSymbol() const {return is(st::CLASS);}

   inline bool
   isFieldSymbol() const {return is(st::FIELD);}

   inline bool
   isFuncSymbol() const {return is(st::FUNCTION);}

   inline bool
   isPrimitiveSymbol() const {return is(st::PRIMITIVE);}

   inline bool
   isPtrSymbol() const {return is(st::POINTER);}

   bool
   isReferenceSymbol() const;

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
