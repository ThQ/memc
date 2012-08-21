#ifndef _MEM__ST__SYMBOL__HPP_
#define _MEM__ST__SYMBOL__HPP_


#include <assert.h>
#include <map>
#include <sstream>
#include <stdio.h>
#include <string>
#include "mem/ss.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/st/SymbolKind.hpp"


namespace mem { namespace st {



// A base class for all symbols stored in the symbol table.
class Symbol
{
   public:
   typedef std::map<std::string, Symbol*> SymbolCollection;
   typedef SymbolCollection::iterator SymbolCollectionIterator;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Symbol ();

   // Destructor.
   virtual
   ~Symbol ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ByteSize
   virtual GETTER(ByteSize, int) {return _byte_size;}
   virtual SETTER(ByteSize, int) {_byte_size = val;}

   // ChildCount
   GETTER(ChildCount, size_t) {return _children.size();}

   virtual st::Symbol*
   gExprType ();

   // Children
   GETTER_REF(Children, SymbolCollection) {return _children;}

   // Depth
   GETTER(Depth, int) {return _depth;}
   SETTER(Depth, int) {_depth = val;}

   // IsInvisible
   GETTER(IsInvisible, bool) {return _is_invisible;}
   SETTER(IsInvisible, bool) {_is_invisible = val;}

   // Kind
   GETTER(Kind, SymbolKind) {return _kind;}

   // Name
   GETTER(Name, std::string) {return _name;}
   SETTER(Name, std::string)
   {
      if (Parent() != NULL)
      {
         Parent()->renameChild(_name, val);
      }
      else
      {
         _name = val;
      }
   }

   // NameCstr
   GETTER(NameCstr, const char*) {return Name().c_str();}
   //void sName (char* name, size_t len);

   // Parent
   GETTER(Parent, st::Symbol*) {return _parent;}
   SETTER(Parent, st::Symbol*) {_parent = val;}


   //--------------------------------------------------------------------------
   // PUBLIC METHODS
   //--------------------------------------------------------------------------
   public:

   // Appends a child symbol.
   virtual bool
   addChild (Symbol* symb);

   // Returns a child given its name.
   virtual Symbol*
   getChild (std::string name);

   std::vector<st::Symbol*>
   getParents ();

   // True if the symbol has children.
   inline bool
   hasChildren() {return _children.size() != 0;}

   // Hints a name for the symbol.
   //
   // It does not actually set it. This is useful for anonymous blocks
   // (if, while, for, ...).
   void
   hintName (Symbol* parent, std::string hint);

   // Returns true if the symbol is of a given kind.
   inline bool
   is (SymbolKind kind) const {return _kind == kind;};

   inline bool
   isAliasSymbol() const {return is(st::ALIAS);}

   bool
   isAnyConstant () const;

   bool
   isAnyPrimitiveType () const;

   bool
   isAnyType () const;

   inline bool
   isArgSymbol() const {return is(st::ARG);}

   inline bool
   isArrayType() const {return is(st::ARRAY);}

   inline bool
   isClassType() const {return is(st::CLASS);}

   inline bool
   isConstantInt() const {return is(st::INT_CONSTANT);}

   inline bool
   isEnumType() const {return is(st::ENUM_TYPE);}

   inline bool
   isFieldSymbol() const {return is(st::FIELD);}

   inline bool
   isFuncSymbol() const {return is(st::FUNCTION);}

   inline bool
   isFunctionType() const {return is(st::FUNCTION_TYPE);}

   inline bool
   isIntConstant () const {return is(st::INT_CONSTANT);}

   inline bool
   isIntType () const {return is(st::INT_TYPE);}

   inline bool
   isMacro () const {return is(st::MACRO);}

   inline bool
   isNamespace () const {return is(st::NAMESPACE);}

   inline bool
   isNullSymbol () const {return is(st::NULL_VALUE);}

   inline bool
   isPointerType() const {return is(st::POINTER);}

   inline bool
   isPrimitiveType() const {return is(st::PRIMITIVE_TYPE);}

   bool
   isReferenceSymbol() const;

   bool
   isTupleType() const {return is(st::TUPLE_TYPE);}

   inline bool
   isVarSymbol() const {return is(st::VAR);}

   inline bool
   isVoidType () const {return is(st::VOID_TYPE);}

   // Returns the qualified name of the symbol.
   //
   // If this symbol is named <Socket> and its parent name is <net>, then it
   // will return <net.Socket>
   virtual std::string
   gQualifiedName();

   // Returns the qualified name as a char pointer.
   inline const char*
   gQualifiedNameCstr() { return this->gQualifiedName().c_str();}

   void
   rename (std::string new_name);

   void
   renameChild (std::string old_name, std::string new_name);

   void
   renameChild (st::Symbol* sym, std::string new_name) {renameChild(sym->Name(), new_name);}

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   // The size in bytes of the symbol. It is only used for types and numeric
   // constants.
   int _byte_size;

   // The number of children.
   size_t _child_count;

   // A hash map of all the children.
   SymbolCollection _children;

   // The depth of the symbol in the whole symbol hierarchy.
   unsigned int _depth;

   bool _is_invisible;

   // The kind of the symbol.
   SymbolKind _kind;

   // The name (id) of the symbol.
   //
   // It does not include the names of the parents.
   std::string _name;

   // The symbol's parent.
   Symbol* _parent;

   // The position in the source where the symbol was encoutered.
   fs::position::Range _pos;
};

typedef std::map<std::string, Symbol*> SymbolMap;
typedef SymbolMap::iterator SymbolMapIterator;
typedef std::vector<Symbol*> SymbolVector;

} }

#endif
