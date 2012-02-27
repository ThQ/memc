#ifndef _MEM__AST__VISITOR__TYPE_MATCH__HPP_
#define _MEM__AST__VISITOR__TYPE_MATCH__HPP_


#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/VarDecl.hpp"
#include "mem/ast/visitor/Visitor.hpp"
#include "mem/fs/position/Composite.hpp"


namespace mem { namespace ast { namespace visitor {


class TypeMatch : public Visitor
{
   public: TypeMatch ();

   public: virtual bool visit (node::Node* node);
   public: void visitVarDecl (node::VarDecl* var_decl_node);
};


} } }

#endif
