#ifndef _MEM__AST__UTIL__HPP_
#define _MEM__AST__UTIL__HPP_


#include <string>


#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/st/Class.hpp"


namespace mem { namespace ast { namespace util {


st::Symbol* find_local_variable_type (node::Node* start_at, std::string var_name);
st::Symbol* find_self_type(node::Node* start_at);


} } }

#endif
