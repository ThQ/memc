#ifndef _MEM__AST__NODE__NODE__HPP
#define _MEM__AST__NODE__NODE__HPP


#include <stdio.h>
#include <vector>
#include "mem/Metadata.hpp"
#include "mem/ast/node/NodeValidator.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/parser/NodeTypes.hpp"
#include "mem/st/Class.hpp"


#define NODE_ENSURE(cond) if (!(cond)){return false;}

namespace mem { namespace ast { namespace node {


class Node
{
   //public: bool _accept_children;
   public: unsigned int _child_count;
   //public: long _expected_child_count;
   public: Node* _first_child;
   public: Node* _last_child;
   public: Node* _next;
   public: fs::position::Range* _position;
   public: Node* _prev;
   public: st::Symbol* _exp_type;


   //--------------------------------------------------------------------------
   // PUBLIC properties
   //--------------------------------------------------------------------------
   public:

   // ----------------------
   // PROPERTY : BoundSymbol
   // ----------------------
   st::Symbol*
   _bound_type;

   inline st::Symbol*
   gBoundSymbol () const {return this->_bound_type;}

   inline void
   sBoundSymbol (st::Symbol* sym) {this->_bound_type = sym;}

   // ---------------------
   // PROPERTY : ChildCount
   // ---------------------
   size_t
   gChildCount() {return this->_child_count;}

   // PROPERTY : Depth
   unsigned long
   _depth;

   void
   sDepth (unsigned long depth);

   // -------------------
   // PROPERTY : ExprType
   // -------------------
   inline st::Type*
   gExprType () {return static_cast<st::Type*>(this->_exp_type);}

   inline void
   sExprType (st::Symbol* sym) {this->_exp_type = sym;};


   // -----------------
   // PROPERTY : Md
   // -----------------
   Metadata* _md;

   inline Metadata*
   gMd() const {return _md;}

   inline bool
   hasMd() const {return _md != NULL;}

   inline void
   sMd (Metadata* md) {_md = md;}

   // -----------------
   // PROPERTY : Parent
   // -----------------
   Node*
   _parent;

   inline Node*
   gParent () const {return this->_parent;}

   // -------------------
   // PROPERTY : Position
   // -------------------
   inline fs::position::Range*
   gPosition() {return this->_position;}

   void
   sPosition(fs::position::Range* pos);

   // ---------------
   // PROPERTY : Type
   // ---------------
   unsigned int _type;

   inline unsigned int
   gType() {return this->_type;}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor
    */
   Node ();

   /**
    * Initializes a node with a specifid type.
    */
   Node (unsigned int type);

   /**
    * Default destructor
    */
   virtual
   ~Node();


   //--------------------------------------------------------------------------
   // PUBLIC methods
   //--------------------------------------------------------------------------
   public:

   inline fs::position::Range*
   copyPosition() { return this->_position->copy_range();}

   /**
    * true if it has a symbol bound.
    */
   inline bool
   hasBoundSymbol () const {return this->_bound_type != NULL;}

   /**
    * true if it has an expression type.
    */
   inline bool
   hasExprType () const {return this->_exp_type != NULL;}

   /**
    * true if the node is of type MEM_NODE_AND.
    */
   inline bool
   isAndNode() const {return isType(MEM_NODE_AND);}

   inline bool
   isBlockNode() {return isType(MEM_NODE_BLOCK);}

   inline bool
   isClassNode() const {return isType(MEM_NODE_CLASS);}

   inline bool
   isDotNode() const {return isType(MEM_NODE_DOT);}

   inline bool
   isFileNode() const {return isType(MEM_NODE_FILE);}

   inline bool
   isFinalIdNode() const {return isType(MEM_NODE_FINAL_ID);}

   inline bool
   isFuncNode() const {return isType(MEM_NODE_FUNCTION_DECLARATION);}

   inline bool
   isFuncParamsNode() const {return isType(MEM_NODE_FUNCTION_PARAMETERS);}

   inline bool
   isIdNode() const {return isType(MEM_NODE_ID);}

   inline bool
   isOrNode() const {return isType(MEM_NODE_OR);}

   inline bool
   isPlaceHolderNode() const {return isType(MEM_NODE_PLACE_HOLDER);}

   inline bool
   isRootNode() const {return isType(MEM_NODE_ROOT);}

   inline bool
   isUseNode() const {return isType(MEM_NODE_USE);}

   /**
    * Returns true if the node is correctly formed after all the compiler
    * checks (but before any optimisation).
    */
   virtual void
   isValid (NodeValidator* vld);

   inline bool
   isVarDeclNode() const {return this->isType(MEM_NODE_VARIABLE_DECLARATION);}

   void
   eat (Node* n);

   /**
    * Returns the type of the node as a string.
    */
   static const char*
   get_type_name (unsigned int type);

   /**
    * Returns the Nth child.
    */
   Node*
   getChild (unsigned int i);

   /**
    * Returns true if the node has children.
    */
   inline bool
   hasChildren () { return this->_child_count > 0; }

   /**
    * Returns true if the node is of any text type.
    */
   bool
   isText ();

   /**
    * Returns true if the node is of a given type.
    */
   inline bool
   isType (unsigned int type) const { return this->_type == type; }

   /**
    * Returns a vector of the node's children types.
    */
   std::vector<st::Symbol*>
   packChildrenExprTypes ();

   /**
    * Appends a child node.
    */
   void
   pushChild (Node*);

   /**
    * Appends 2 children nodes.
    */
   inline void
   pushChildren (Node* n1, Node* n2)
   {
      this->pushChild(n1);
      this->pushChild(n2);
   }

   /**
    * Appends 3 children nodes.
    */
   inline void
   pushChildren (Node* n1, Node* n2, Node* n3)
   {
      this->pushChild(n1);
      this->pushChild(n2);
      this->pushChild(n3);
   }

   /**
    * Replaces a child node with another node.
    */
   bool
   replaceChild (Node* search, Node* replace);

   /**
    * Unlinks this node so that it is not pointed to by its parent, siblings,
    * etc.
    */
   void
   unlink ();
};


} } }

#endif
