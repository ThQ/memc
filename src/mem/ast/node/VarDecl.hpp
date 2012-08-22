#ifndef _MEM__AST__NODE__VARDECL__HPP_
#define _MEM__AST__NODE__VARDECL__HPP_


#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class VarDecl : public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   VarDecl ();


   //--------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}

   // Name
   GETTER(Name, std::string) {return NameNode()->_value;}

   // NameCstr
   GETTER(NameCstr, const char*) {return Name().c_str();}

   // NameNode
   GETTER(NameNode, Text*) { return static_cast<Text*>(getChild(0)); }

   // TypeNode
   GETTER(TypeNode, Node*) { return getChild(1); }

   // ValueNode
   GETTER(ValueNode, Node*) { return getChild(2); }


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }


#endif
