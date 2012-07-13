#ifndef _MEM__AST__NODE__VARDECL__HPP_
#define _MEM__AST__NODE__VARDECL__HPP_


#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class VarDecl : public Node
{
   public: VarDecl ();

   public: inline std::string gName() { return this->gNameNode()->_value; }
   public: inline const char* gNameCstr() {return this->gName().c_str();}
   public: inline Text* gNameNode() { return static_cast<Text*>(this->getChild(0)); }
   public: inline Node* gTypeNode() { return this->getChild(1); }
   public: inline Node* gValueNode() { return this->getChild(2); }
   public: virtual void isValid (NodeValidator* v);
};


} } }

#endif
