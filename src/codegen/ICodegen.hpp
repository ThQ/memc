#ifndef __MEM__CODEGEN__I_CODE_GENERATOR_HPP__
#define __MEM__CODEGEN__I_CODE_GENERATOR_HPP__


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Field.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Number.hpp"
#include "mem/ast/node/Root.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Use.hpp"
#include "mem/ast/node/VarDecl.hpp"
#include "mem/st/SymbolTable.hpp"


namespace codegen {


class ICodegen
{
   //public: virtual void gen (ast::node::Node* root);
};


}

#endif
