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
#include "mem/st/FunctionType.hpp"
#include "mem/st/IntConstant.hpp"
#include "mem/st/IntType.hpp"
#include "mem/st/Null.hpp"
#include "mem/st/PrimitiveType.hpp"
#include "mem/st/PointerType.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/st/TupleType.hpp"
#include "mem/st/Type.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace st { namespace util {


st::Namespace*
createNamespace (Symbol* scope, std::vector<std::string> ns_name_parts);

inline IntType*
getBiggestIntType (st::IntType* t1, st::IntType* t2)
{
   DEBUG_REQUIRE (t1 != NULL);
   DEBUG_REQUIRE (t2 != NULL);
   return t1->ByteSize() >= t2->ByteSize() ? t1 : t2;
}

Type*
getExprType (Symbol* s);

FunctionType*
getFunctionType (Symbol* scope, TypeVector tys, Type* return_type);

IntConstant*
getNativeShortConstant (Symbol* scope, short i);

IntConstant*
getNativeCharConstant (Symbol* scope, char i);

IntConstant*
getNativeIntConstant (Symbol* scope, int i);

Type*
getPointerBaseType(PointerType* ptr);

PointerType*
getPointerType (Type* base_ty);

Symbol*
getSymbol (Symbol* scope, std::string symbol_name);

TupleType*
getTupleType (Symbol* scope, TypeVector tys);

size_t
getIndirectionCount (std::string type_name);

ArrayType*
getSizedArrayType (st::Type* item_ty, int size);

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

bool
isFunctorType (Symbol* s);

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
