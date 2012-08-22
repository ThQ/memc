#ifndef _MEM__AST__UTIL__HPP_
#define _MEM__AST__UTIL__HPP_


#include <string>


#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Dot.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/FinalId.hpp"
#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/While.hpp"
#include "mem/st/Class.hpp"
#include "mem/st/Func.hpp"
#include "mem/Util.hpp"


namespace mem { namespace ast { namespace util {

template<class T, unsigned int NodeKind>
T
castTo (node::Node* n){assert(n->isKind(NodeKind));return static_cast<T>(n);}

node::Call*
createCall (std::string qualified_name, ast::node::Node* arg);

node::File*
getFileNode (node::Node* cur_node);

st::Func*
getParentFunction (node::Node* cur_node);


} } }

#endif
