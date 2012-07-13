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
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   inline std::string
   gName() { return this->gNameNode()->_value; }

   inline const char*
   gNameCstr() {return this->gName().c_str();}

   inline Text*
   gNameNode() { return static_cast<Text*>(this->getChild(0)); }

   inline Node*
   gTypeNode() { return this->getChild(1); }

   inline Node*
   gValueNode() { return this->getChild(2); }

   virtual void
   isValid (NodeValidator* v);
};


} } }


#endif
