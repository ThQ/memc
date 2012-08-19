#ifndef _MEM__AST__NODE__NODE__HPP
#define _MEM__AST__NODE__NODE__HPP


#include <stdio.h>
#include <vector>
#include "mem/Metadata.hpp"
#include "mem/ss.hpp"
#include "mem/ast/node/Kind.hpp"
#include "mem/ast/node/NodeValidator.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/st/Class.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace ast { namespace node {


class Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Node ();

   // Initializes a node with a specifid type.
   Node (unsigned int type);

   // Default destructor
   virtual
   ~Node();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // BoundSymbol
   GETTER(BoundSymbol, st::Symbol*) {return _bound_type;}
   SETTER(BoundSymbol, st::Symbol*) {_bound_type = val;}

   // ChildCount
   GETTER(ChildCount, size_t) {return _child_count;}

   // Depth
   void Depth (unsigned long depth);

   // ExprType
   GETTER(ExprType, st::Type*) {return _exp_type;}
   SETTER(ExprType, st::Type*) {_exp_type = val;}
   SETTER(ExprType, st::Symbol*) {assert(val->isAnyType());_exp_type = static_cast<st::Type*>(val);}

   // Kind
   GETTER(Kind, unsigned int) {return _type;}
   SETTER(Kind, unsigned int) {_type = val;}

   // KindName
   GETTER(KindName, std::string) {return get_type_name(_type);}
   GETTER(KindNameCstr, const char*) {return get_type_name(_type);}

   // Metadata
   GETTER(Metadata, class mem::Metadata*) {return _md;}
   SETTER(Metadata, class Metadata*) {_md = val;}

   // Parent
   GETTER(Parent, Node*) {return _parent;}

   // Position
   GETTER(Position, fs::position::Range*) {return _position;}
   SETTER(Position, fs::position::Range*) {_position = val;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   copy () const {assert(false);return NULL;}

   inline fs::position::Range*
   copyPosition() { return _position != NULL ? _position->copy_range() : NULL;}

   // true if it has a symbol bound.
   inline bool
   hasBoundSymbol () const {return _bound_type != NULL;}

   // true if it has an expression type.
   inline bool
   hasExprType () const {return _exp_type != NULL;}

   inline bool
   hasMetadata() const {return _md != NULL;}

   void
   insertChild (Node* n);

   inline bool
   isAmpersandNode() const {return isKind(Kind::AMPERSAND);}

   // true if the node is of type MEM_NODE_AND.
   inline bool
   isAndNode() const {return isKind(Kind::OP_AND);}

   bool
   isAssignable ();

   inline bool
   isArrayNode() {return isKind(Kind::ARRAY);}

   inline bool
   isBlockNode() {return isKind(Kind::BLOCK);}

   inline bool
   isClassNode() const {return isKind(Kind::CLASS);}

   inline bool
   isDecoratorNode() const {return isKind(Kind::DECORATOR);}

   inline bool
   isDotNode() const {return isKind(Kind::DOT);}

   inline bool
   isEnumNode() const {return isKind(Kind::ENUM);}

   inline bool
   isFieldNode() const {return isKind(Kind::FIELD);}

   inline bool
   isFileNode() const {return isKind(Kind::FILE);}

   inline bool
   isFinalIdNode() const {return isKind(Kind::FINAL_ID);}

   inline bool
   isFuncNode() const {return isKind(Kind::FUNCTION);}

   inline bool
   isFuncParamsNode() const {return isKind(Kind::FUNCTION_PARAMETERS);}

   inline bool
   isLastChild (Node* s) {return _last_child == s;}

   inline bool
   isIdNode() const {return isKind(Kind::ID);}

   inline bool
   isNewNode() const {return isKind(Kind::NEW);}

   inline bool
   isNumberNode() const {return isKind(Kind::NUMBER);}

   inline bool
   isOrNode() const {return isKind(Kind::OP_OR);}

   inline bool
   isPlaceHolderNode() const {return isKind(Kind::PLACE_HOLDER);}

   bool
   isReferenceNode() const;

   inline bool
   isReturnNode() const {return isKind(Kind::RETURN);}

   inline bool
   isRootNode() const {return isKind(Kind::ROOT);}

   inline bool
   isStringNode() const {return isKind(Kind::STRING);}

   inline bool
   isUseNode() const {return isKind(Kind::USE);}

   // Returns true if the node is correctly formed after all the compiler
   // checks (but before any optimisation).
   virtual void
   isValid (NodeValidator* vld);

   inline bool
   isVarDeclNode() const {return isKind(Kind::VARIABLE_DECLARATION);}

   void
   eat (Node* n);

   // Returns the type of the node as a string.
   static const char*
   get_type_name (int type);

   // Returns the Nth child.
   Node*
   getChild (unsigned int i) const;

   // Returns true if the node has children.
   inline bool
   hasChildren () { return _child_count > 0; }

   // Returns true if the node is of any text type.
   bool
   isText ();

   // Returns true if the node is of a given type.
   inline bool
   isKind (unsigned int kind) const { return _type == kind; }

   // Returns a vector of the node's children types.
   st::TypeVector
   packChildrenExprTypes ();

   // Appends a child node.
   void
   pushChild (Node*);

   // Appends 2 children nodes.
   inline void
   pushChildren (Node* n1, Node* n2)
   {
      pushChild(n1);
      pushChild(n2);
   }

   // Appends 3 children nodes.
   inline void
   pushChildren (Node* n1, Node* n2, Node* n3)
   {
      pushChild(n1);
      pushChild(n2);
      pushChild(n3);
   }

   // Appends 4 children nodes.
   inline void
   pushChildren (Node* n1, Node* n2, Node* n3, Node* n4)
   {
      pushChild(n1);
      pushChild(n2);
      pushChild(n3);
      pushChild(n4);
   }

   Node*
   removeChild (Node* search);

   // Replaces a child node with another node.
   bool
   replaceChild (Node* search, Node* replace);

   // Unlinks this node so that it is not pointed to by its parent, siblings,
   // etc.
   void
   unlink ();

   void
   unlinkChildren ();


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   st::Symbol* _bound_type;
   size_t _child_count;
   unsigned long _depth;
   st::Type* _exp_type;
   Node* _first_child;
   Node* _last_child;
   Node* _next;
   Node* _parent;
   fs::position::Range* _position;
   Node* _prev;
   mem::Metadata* _md;
   int _type;
};

void
assertKind (Node* n, int k);

} } }

#endif
