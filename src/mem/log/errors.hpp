#ifndef _MEM__LOG__ERRORS__HPP_
#define _MEM__LOG__ERRORS__HPP_


// ----------------------------------------------------------------------------
// !!! DONT EDIT MANUALLY !!!
// Generated
//    by <utils/GenErrorClasses.py>
//    from <src/mem/log/errors.errors-in>
// ----------------------------------------------------------------------------


#include "mem/log/Message.hpp"

namespace mem { namespace log {


class EntryPointNotFound : public FatalError
{
   public: inline void format() {formatMessage("Entry point not found ");formatDescription("Declare a main function (anywhere) :%NEWLINE   main () -> int ");}
};

class CannotInstantiatePointerType : public Error
{
   public: std::string _PointerTypeName;

   public: inline void sPointerTypeName(std::string PointerTypeName) {_PointerTypeName=PointerTypeName;}
   public: inline void format() {formatMessage("Pointer types cannot be instantiated ");formatDescription("Trying to instantiate pointer type %s ", _PointerTypeName.c_str());}
};

class SpecificTypeExpected : public Error
{
   public: std::string _ExpectedTypeName;
   public: std::string _TypeName;

   public: inline void sExpectedTypeName(std::string ExpectedTypeName) {_ExpectedTypeName=ExpectedTypeName;}
   public: inline void sTypeName(std::string TypeName) {_TypeName=TypeName;}
   public: inline void format() {formatMessage("Expression of type %s expected, but got %s instead ", _ExpectedTypeName.c_str(), _TypeName.c_str());}
};

class BadParameterCount : public Error
{
   public: int _ExpectedParamCount;
   public: int _ParamCount;

   public: inline void sExpectedParamCount(int ExpectedParamCount) {_ExpectedParamCount=ExpectedParamCount;}
   public: inline void sParamCount(int ParamCount) {_ParamCount=ParamCount;}
   public: inline void format() {formatMessage("Bad parameter count : expected %d, but got %d ", _ExpectedParamCount, _ParamCount);}
};

class SymbolNotFound : public Error
{
   public: std::string _ScopeName;
   public: std::string _SymbolName;

   public: inline void sScopeName(std::string ScopeName) {_ScopeName=ScopeName;}
   public: inline void sSymbolName(std::string SymbolName) {_SymbolName=SymbolName;}
   public: inline void format() {formatMessage("Symbol %s not found in %s ", _SymbolName.c_str(), _ScopeName.c_str());}
};

class VariableAlreadyDefined : public Error
{
   public: std::string _VarName;

   public: inline void sVarName(std::string VarName) {_VarName=VarName;}
   public: inline void format() {formatMessage("Variable %s already defined ", _VarName.c_str());}
};

class CallNonFunction : public Error
{
   public: std::string _ObjectTypeName;
   public: std::string _ObjectName;

   public: inline void sObjectTypeName(std::string ObjectTypeName) {_ObjectTypeName=ObjectTypeName;}
   public: inline void sObjectName(std::string ObjectName) {_ObjectName=ObjectName;}
   public: inline void format() {formatMessage("Trying to call an object (%s) that is not a function, but a %s ", _ObjectName.c_str(), _ObjectTypeName.c_str());}
};

class TypeExpected : public Error
{
   public: std::string _SymbolName;

   public: inline void sSymbolName(std::string SymbolName) {_SymbolName=SymbolName;}
   public: inline void format() {formatMessage("%s is not a type ", _SymbolName.c_str());}
};

class InvalidTypeInVarAssignment : public Error
{
   public: std::string _ExpectedTypeName;
   public: std::string _VariableName;
   public: std::string _TypeName;

   public: inline void sExpectedTypeName(std::string ExpectedTypeName) {_ExpectedTypeName=ExpectedTypeName;}
   public: inline void sVariableName(std::string VariableName) {_VariableName=VariableName;}
   public: inline void sTypeName(std::string TypeName) {_TypeName=TypeName;}
   public: inline void format() {formatMessage("Types mismatch in variable assigment ");formatDescription("Variable %s expects value of type %s, but got %s instead ", _VariableName.c_str(), _ExpectedTypeName.c_str(), _TypeName.c_str());}
};

class CircularClassDependency : public FatalError
{
   public: std::string _BaseClassName;
   public: std::string _DepClassName;

   public: inline void sBaseClassName(std::string BaseClassName) {_BaseClassName=BaseClassName;}
   public: inline void sDepClassName(std::string DepClassName) {_DepClassName=DepClassName;}
   public: inline void format() {formatMessage("Circular dependency ");formatDescription("Class %s depends on class %s and vice verso ", _BaseClassName.c_str(), _DepClassName.c_str());}
};



} }


#endif
