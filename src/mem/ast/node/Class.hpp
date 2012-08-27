#ifndef _MEM__AST__NODE__CLASS__HPP_
#define _MEM__AST__NODE__CLASS__HPP_


#include "mem/ast/node/FinalId.hpp"
#include "mem/ast/node/NodeList.hpp"
#include "mem/ast/node/Type.hpp"


namespace mem { namespace ast { namespace node {


class Class : public Type
{
   public:
   static const int kTYPE = Kind::CLASS;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Class ();

   // Destructor
   virtual
   ~Class ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return 3;}

   GETTER(MembersNode, NodeList*) {return _members_node;}
   SETTER(MembersNode, NodeList*)
   {
      _members_node = val;
      if (val != NULL) val->setParent(this);
   }

   GETTER(NameNode, Node*) {return _name_node;}
   SETTER(NameNode, Node*)
   {
      _name_node = val;
      if (val != NULL) val->setParent(this);
   }

   GETTER(ParentTypeNode, Node*) {return _parent_type_node;}
   SETTER(ParentTypeNode, Node*)
   {
      _parent_type_node = val;
      if (val != NULL) val->setParent(this);
   }

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   getChild (size_t i) const;

   virtual void
   setChild (size_t i, Node* n);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   Node* _name_node;
   Node* _parent_type_node;
   NodeList* _members_node;
};


} } }

#endif
