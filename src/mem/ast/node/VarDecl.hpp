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

   inline Text*
   NameNode() { return static_cast<Text*>(getChild(0)); }

   inline Node*
   TypeNode() { return getChild(1); }

   inline Node*
   ValueNode() { return getChild(2); }


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   inline std::string
   gName() { return this->NameNode()->_value; }

   inline const char*
   gNameCstr() {return this->gName().c_str();}

   virtual void
   isValid (NodeValidator* v);
};


} } }


#endif
