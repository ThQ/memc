#ifndef _MEM__AST__NODE__NODE__HPP
#define _MEM__AST__NODE__NODE__HPP


#include <sstream>
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


   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Node ();

   // Default destructor
   virtual
   ~Node ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // BoundSymbol
   st::Symbol*
   BoundSymbol() const {return _bound_type;}

   void
   setBoundSymbol(st::Symbol* val) {_bound_type = val;}

   // ChildCount
   virtual
   GETTER(ChildCount, size_t) {return 0;}

   // Depth
   void Depth (unsigned long depth);

   // ExprType
   st::Type*
   ExprType () const {return _exp_type;}

   void
   setExprType (st::Type* val) {_exp_type = val;}

   void
   setExprType (st::Symbol* val) {assert(st::isa<st::Type>(val));_exp_type = st::cast<st::Type>(val);}

   // Kind
   int
   Kind () const {return _type;}

   void
   setKind (int val) {_type = val;}

   // KindName
   std::string
   KindName () const {return get_type_name(_type);}

   // KindNameCstr
   const char*
   KindNameCstr () const {return get_type_name(_type);}

   // MemorySize
   virtual int
   MemorySize () const {return sizeof(Node);}

   // Parent
   Node*
   Parent() const {return _parent;}

   void
   setParent (Node* val) {_parent = val; assert(_checkCircularDependencies());}

   // Position
   fs::position::Range*
   Position () const {return _position;}

   void
   setPosition (fs::position::Range* val) {_position = val;}

   // StringRep
   std::string
   StringRep () const
   {
      std::ostringstream str;
      str << "[@" << static_cast<const void*>(this);
      str << ", " << KindName();
      str << "]";
      return str.str();
   }

   // Value
   std::string
   Value () const {return _value;}

   void
   setValue (std::string val) {_value = val;}

   // ValueCstr
   const char*
   ValueCstr () const {return _value.c_str();}


   //==========================================================================
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
   isKind (int kind) const { return _type == kind; }

   // Returns a vector of the node's children types.
   st::TypeVector
   packChildrenExprTypes ();

   // Replaces a child node with another node.
   bool
   replaceChild (Node* search, Node* replace);

   virtual void
   setChild (size_t i, Node* n) {}


   //--------------------------------------------------------------------------
   // PROTECTED FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   bool
   _checkCircularDependencies ();


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
         DEBUG_PRINTF("Invalid cast: node @%p is NULL\n", n);
         assert(false);
      }
      else if (!node::canCast(n->Kind(), T::kTYPE))
      {
         DEBUG_PRINTF("Invalid cast: cannot cast from %s (@%p) to %s\n",
            Node::get_type_name(n->Kind()),
            n,
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
