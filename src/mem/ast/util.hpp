#ifndef _MEM__AST__UTIL__HPP_
#define _MEM__AST__UTIL__HPP_


#include <string>


#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/st/Class.hpp"
#include "mem/st/Func.hpp"


namespace mem { namespace ast { namespace util {


node::File*
getFileNode (node::Node* cur_node);

st::Func*
getParentFunction (node::Node* cur_node);


} } }

#endif
