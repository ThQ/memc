#ifndef _MEM__ST__UTIL__HPP_
#define _MEM__ST__UTIL__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/st/Alias.hpp"
#include "mem/st/ArrayType.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/st/PrimitiveType.hpp"
#include "mem/st/PointerType.hpp"
#include "mem/st/Type.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace st { namespace util {


st::Namespace*
createNamespace (Symbol* scope, std::vector<std::string> ns_name_parts);

Type*
getExprType (Symbol* s);

Type*
getPointerBaseType(PointerType* ptr);

PointerType*
getPointerType (Type* base_ty);

Symbol*
getSymbol (Symbol* scope, std::string symbol_name);

size_t
getIndirectionCount (std::string type_name);

/**
 * Get or create an unsized array type from a sized array type.
 */
ArrayType*
getUnsizedArrayType (st::ArrayType* sized_arr);

/**
 * Get or create an unsized array type from its base type.
 */
ArrayType*
getUnsizedArrayType (st::Type* base_ty);

ArrayType*
lookupArrayType (Symbol* scope, std::string base_ty_name, int size);

Class*
lookupClass (Symbol* scope, std::string cls_name);

Func*
lookupFunction (Symbol* scope, std::string func_name);

PointerType*
lookupPointer(Symbol* scope, std::string base_ty_name, size_t ptr_level);

PointerType*
lookupPointer(Symbol* scope, Type* base_ty);

Symbol*
lookupMember (Symbol* scope, std::string symbol_name);

Symbol*
lookupSymbol (Symbol* scope, std::string symbol_name);

Symbol*
lookupSymbol (Symbol* scope, std::vector<std::string> name_parts);

bool
parseArrayTypeName (std::string name, std::string& base_ty_name, int& array_len);

void
registerType (SymbolTable* st, Symbol* scope, Type* ty);

void
setupBool (SymbolTable& st, CoreTypes& core_types);

void
setupBugType (SymbolTable& st, CoreTypes& core_types);

void
setupInts (SymbolTable& st, CoreTypes& core_types);

void
setupVoid (SymbolTable& st, CoreTypes& core_types);

std::vector<std::string>
splitQualifiedName (std::string name);
};


} }

#endif
