#ifndef _MEM__AST__NODE__DECORATOR__HPP_
#define _MEM__AST__NODE__DECORATOR__HPP_


#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class Decorator : public Text
{
   public:
   static const int kTYPE = MetaKind::DECORATOR;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Decorator ();

   // Destructor
   virtual
   ~Decorator ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER (MemorySize, int) {return sizeof(Decorator);}

   GETTER (NameNode, Node*) {return _nodeName;}
   SETTER (NameNode, Node*)
   {
      _nodeName = val;
      if (val != NULL) val->setParent(this);
   }


   //==========================================================================
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   getChild (size_t i) const;

   virtual void
   isValid (NodeValidator* v);

   virtual void
   setChild (size_t i, Node* n);


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   Node* _nodeName;
};

} } }

#endif
