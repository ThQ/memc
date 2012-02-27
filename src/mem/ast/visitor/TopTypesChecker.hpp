#ifndef _MEM__AST__VISITOR__TOP_TYPES_CHECKER__HPP_
#define _MEM__AST__VISITOR__TOP_TYPES_CHECKER__HPP_


#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Field.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Type.hpp"
#include "mem/ast/visitor/TypeChecker.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/st/FunctionSignature.hpp"
#include "mem/st/Util.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace ast { namespace visitor {

class TopTypesChecker : public TypeChecker
{
   public: TopTypesChecker ();

   public: virtual bool visit (node::Node* node);
   public: virtual void visitField (st::Symbol* scope, node::Field* field);
   public: virtual void visitFuncDecl (st::Symbol* scope, node::Func* func_decl);
   public: virtual void visitFuncParams (st::Symbol* scope, node::Node* params_node, st::FunctionSignature* func_sign_sym);
   public: virtual void visitFuncReturnType (node::Func* func_node, st::Func* func_sym, st::FunctionSignature* func_sign_sym);
   public: virtual void visitQualifiedName (st::Symbol* scope, node::Text* name_node);
};


} } }

#endif
