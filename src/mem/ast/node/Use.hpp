#ifndef _MEM__AST__NODE__USE__HPP_
#define _MEM__AST__NODE__USE__HPP_


#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/FinalId.hpp"


namespace mem { namespace ast { namespace node {


class Use: public Node
{
   public:
   static const int kTYPE = MetaKind::USE;


   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Use ();

   // Destructor
   ~Use ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return 1;}

   // IdNode
   GETTER(IdNode, FinalId*) {return _nodeId;}
   SETTER(IdNode, FinalId*) {
      _nodeId = val;
      if (val != NULL) val->setParent(this);
   }

   virtual
   GETTER (MemorySize, int) {return sizeof(Use);}


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   getChild (size_t i) const;

   void
   isValid (NodeValidator* v);

   virtual void
   setChild (size_t i, Node* n);


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   node::FinalId* _nodeId;

};


} } }


#endif
