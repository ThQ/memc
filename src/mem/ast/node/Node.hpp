#ifndef _MEM__AST__NODE__NODE__HPP
#define _MEM__AST__NODE__NODE__HPP


#include <stdio.h>
#include <vector>
#include "mem/ss.hpp"
#include "mem/ast/node/Kind.hpp"
#include "mem/ast/node/NodeValidator.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/st/Class.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace ast { namespace node {

class Node
{
   public:
   static const int kTYPE = MetaKind::UNKNOWN;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Node ();

   // Default destructor
   virtual
   ~Node ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // BoundSymbol
   GETTER(BoundSymbol, st::Symbol*) {return _bound_type;}
   SETTER(BoundSymbol, st::Symbol*) {_bound_type = val;}

   // ChildCount
   virtual
   GETTER(ChildCount, size_t) {return 0;}

   // Depth
   void Depth (unsigned long depth);

   // ExprType
   GETTER(ExprType, st::Type*) {return _exp_type;}
   SETTER(ExprType, st::Type*) {_exp_type = val;}
   SETTER(ExprType, st::Symbol*) {assert(val->isAnyType());_exp_type = static_cast<st::Type*>(val);}

   // Kind
   GETTER(Kind, int) {return _type;}
   SETTER(Kind, int) {_type = val;}

   // KindName
   GETTER(KindName, std::string) {return get_type_name(_type);}
   GETTER(KindNameCstr, const char*) {return get_type_name(_type);}

   // MemorySize
   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}

   // Parent
   GETTER(Parent, Node*) {return _parent;}
   SETTER(Parent, Node*) {_parent = val;}

   // Position
   GETTER(Position, fs::position::Range*) {return _position;}
   SETTER(Position, fs::position::Range*) {_position = val;}

   // Value
   GETTER(Value, std::string) {return _value;}
   SETTER(Value, std::string) {_value = val;}

   // ValueCstr
   GETTER(ValueCstr, const char*) {return _value.c_str();}

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

#if 0
   void
   eat (Node* n);
#endif

   // Returns the type of the node as a string.
   static const char*
   get_type_name (int type);

   // Returns the Nth child.
   virtual Node*
   getChild (size_t i) const;

   // Returns true if the node has children.
   inline bool
   hasChildren () { return ChildCount() > 0; }

   void
   insertChild (Node* n);

   bool
   isAssignable ();

   bool
   isReferenceNode () const;

   // Returns true if the node is correctly formed after all the compiler
   // checks (but before any optimisation).
   virtual void
   isValid (NodeValidator* vld);

   // Returns true if the node is of a given type.
   inline bool
   isKind (unsigned int kind) const { return _type == kind; }

   // Returns a vector of the node's children types.
   st::TypeVector
   packChildrenExprTypes ();

   // Replaces a child node with another node.
   bool
   replaceChild (Node* search, Node* replace);

   virtual void
   setChild (size_t i, Node* n) {}


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   st::Symbol* _bound_type;
   st::Type* _exp_type;
   Node* _parent;
   fs::position::Range* _position;
   int _type;
   std::string _value;
};

template <class T> T*
cast (Node* n)
{
   IF_DEBUG
   {
      if (n == NULL)
      {
         DEBUG_PRINTF("Invalid cast: node @%x is NULL\n", (int)n);
         assert(false);
      }
      else if (!node::canCast(n->Kind(), T::kTYPE))
      {
         DEBUG_PRINTF("Invalid cast: cannot cast from %s to %s\n",
            Node::get_type_name(n->Kind()),
            Node::get_type_name(T::kTYPE));
         assert(false);
      }
   }
   return static_cast<T*>(n);
}

template <class T> bool
isa (Node* n)
{
   if (n != NULL) return node::canCast(n->Kind(), T::kTYPE);
   return false;
}

void
assertKind (Node* n, int k);

} } }

#endif
