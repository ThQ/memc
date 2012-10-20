#ifndef _MEM__AST__NODE__NODE_LIST__HPP_
#define _MEM__AST__NODE__NODE_LIST__HPP_


#include <vector>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class NodeList: public Node
{
   public:
   static const int kTYPE = MetaKind::NODE_LIST;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Constructor
   NodeList ();

   // Destructor
   virtual
   ~NodeList ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return _children.size();}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   addChild (Node* n);

   void
   eat (NodeList* n);

   virtual Node*
   getChild (size_t i) const;

   void
   insertChild (Node* n);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   std::vector<Node*> _children;
};

} } }

#endif
