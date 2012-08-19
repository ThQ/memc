cmake_minimum_required(VERSION 2.8)

#------------------------------------------------------------------------------
# PREREQUISITES
#------------------------------------------------------------------------------
enable_language(C)
enable_language(CXX)

include(${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)

find_program(PYTHON python)
find_program(BISON bison)
find_program(LLVM_CONFIG_EXE NAMES "llvm-config" "llvm-config-3.0")

set(memc_BUILT ${CMAKE_CURRENT_BINARY_DIR}/src.built)
set(memc_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(memc_UTILS ${CMAKE_CURRENT_SOURCE_DIR}/utils)

file(MAKE_DIRECTORY ${memc_BUILT})
file(MAKE_DIRECTORY ${memc_BUILT}/mem/lang)

if(${LLVM_CONFIG_EXE} STREQUAL "LLVM_CONFIG_EXE-NOTFOUND")
	message(WARNING "llvm-config executable not found, compiling without native code generation")
else()
	SET(HAVE_LLVM 1)
	execute_process(COMMAND ${LLVM_CONFIG_EXE} --cppflags OUTPUT_VARIABLE LLVM_CPP_FLAGS)
	STRING(REPLACE "\n" " " LLVM_CPP_FLAGS "${LLVM_CPP_FLAGS}")
	STRING(REPLACE "\r" " " LLVM_CPP_FLAGS "${LLVM_CPP_FLAGS}")
	#execute_process(COMMAND ${LLVM_CONFIG_EXE} --ldflags OUTPUT_VARIABLE LLVM_LD_FLAGS)
	execute_process(COMMAND ${LLVM_CONFIG_EXE} --ldflags --libs OUTPUT_VARIABLE LLVM_LIBS)
	STRING(REPLACE "\n" " " LLVM_LIBS "${LLVM_LIBS}")
	STRING(REPLACE "\r" " " LLVM_LIBS "${LLVM_LIBS}")
	STRING(REGEX REPLACE " $" "" LLVM_LIBS "${LLVM_LIBS}")
	set(CMAKE_CXX_FLAGS ${LLVM_CPP_FLAGS})
	INCLUDE(CheckLibraryExists)
	CHECK_LIBRARY_EXISTS(dl dladdr "" HAVE_LIBDL)
endif()

CHECK_INCLUDE_FILE("stdint.h" HAVE_STDINT_H)

#------------------------------------------------------------------------------
# CUSTOM COMMANDS
#------------------------------------------------------------------------------
# Node kinds
add_custom_command(
	OUTPUT
		${memc_BUILT}/mem/ast/node/Kind.hpp
		${memc_BUILT}/mem/ast/node/Kind.cpp
	COMMAND
		${PYTHON} ${memc_UTILS}/GenNodeTypes.py
		--template="${memc_SRC}/mem/ast/node/Kind.kind-in"
		--output-hpp-file="${memc_BUILT}/mem/ast/node/Kind.hpp"
		--output-cpp-file="${memc_BUILT}/mem/ast/node/Kind.cpp"
	DEPENDS ${memc_UTILS}/GenNodeTypes.py)
add_custom_target(
	gen-node-types ALL
	DEPENDS
		${memc_BUILT}/mem/ast/node/Kind.hpp
		${memc_BUILT}/mem/ast/node/Kind.cpp)

# Error classes
add_custom_command(
	OUTPUT ${memc_BUILT}/mem/log/errors.hpp
	COMMAND
		${PYTHON} ${memc_UTILS}/GenErrorClasses.py
		--template="${memc_SRC}/mem/log/errors.errors-in"
		--output-hpp-file="${memc_BUILT}/mem/log/errors.hpp"
	DEPENDS
		${memc_UTILS}/GenErrorClasses.py
		${memc_SRC}/mem/log/errors.errors-in)
add_custom_target(
	gen-error-classes ALL
	DEPENDS ${memc_BUILT}/mem/log/errors.hpp)

# Bison parser + Token kinds
add_custom_command(
	OUTPUT
		${memc_BUILT}/mem/lang/Bison.hpp
		${memc_BUILT}/mem/lang/Bison.cpp
	COMMAND
		${BISON} -y
		-d ${memc_SRC}/mem/lang/Bison.ypp
		-o ${memc_BUILT}/mem/lang/Bison.cpp
	COMMAND
		${PYTHON} ${memc_UTILS}/GenTokenKind.py
		${memc_BUILT}/mem/lang/Bison.hpp
		${memc_BUILT}/mem/lang/TokenKind.hpp
	DEPENDS
		${BISON}
		${memc_SRC}/mem/lang/Bison.ypp)
add_custom_target(
	bison-parser ALL
	DEPENDS
		${memc_BUILT}/mem/lang/Bison.hpp
		${memc_BUILT}/mem/lang/Bison.cpp)


#------------------------------------------------------------------------------
# memc
#------------------------------------------------------------------------------

project(memc CXX)

set(memc_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/bin/mem-compile/main.cpp
	${memc_SRC}/mem/Compiler.cpp
	${memc_SRC}/mem/Metadata.cpp
	${memc_SRC}/mem/number.cpp
	${memc_SRC}/mem/Util.cpp
	${memc_SRC}/mem/ast/util.cpp
	${memc_SRC}/mem/ast/macro/Macro.cpp
	${memc_SRC}/mem/ast/macro/PtrMacros.cpp
	${memc_SRC}/mem/ast/node/Array.cpp
	${memc_SRC}/mem/ast/node/BinaryExpression.cpp
	${memc_SRC}/mem/ast/node/BinaryOp.cpp
	${memc_SRC}/mem/ast/node/Block.cpp
	${memc_SRC}/mem/ast/node/BracketOp.cpp
	${memc_SRC}/mem/ast/node/Call.cpp
	${memc_SRC}/mem/ast/node/CastOp.cpp
	${memc_SRC}/mem/ast/node/Class.cpp
	${memc_SRC}/mem/ast/node/Decorator.cpp
	${memc_SRC}/mem/ast/node/Dot.cpp
	${memc_SRC}/mem/ast/node/Enum.cpp
	${memc_SRC}/mem/ast/node/Field.cpp
	${memc_SRC}/mem/ast/node/File.cpp
	${memc_SRC}/mem/ast/node/FinalId.cpp
	${memc_SRC}/mem/ast/node/For.cpp
	${memc_SRC}/mem/ast/node/Func.cpp
	${memc_SRC}/mem/ast/node/If.cpp
	${memc_BUILT}/mem/ast/node/Kind.cpp
	${memc_SRC}/mem/ast/node/New.cpp
	${memc_SRC}/mem/ast/node/Node.cpp
	${memc_SRC}/mem/ast/node/NodeValidator.cpp
	${memc_SRC}/mem/ast/node/Number.cpp
	${memc_SRC}/mem/ast/node/Primitive.cpp
	${memc_SRC}/mem/ast/node/Ptr.cpp
	${memc_SRC}/mem/ast/node/Return.cpp
	${memc_SRC}/mem/ast/node/Root.cpp
	${memc_SRC}/mem/ast/node/String.cpp
	${memc_SRC}/mem/ast/node/Text.cpp
	${memc_SRC}/mem/ast/node/Tuple.cpp
	${memc_SRC}/mem/ast/node/TupleType.cpp
	${memc_SRC}/mem/ast/node/Type.cpp
	${memc_SRC}/mem/ast/node/Use.cpp
	${memc_SRC}/mem/ast/node/VarAssign.cpp
	${memc_SRC}/mem/ast/node/VarDecl.cpp
	${memc_SRC}/mem/ast/node/While.cpp
	${memc_SRC}/mem/ast/visitor/BlockTypesChecker.cpp
	${memc_SRC}/mem/ast/visitor/CheckValidity.cpp
	${memc_SRC}/mem/ast/visitor/Ctor.cpp
	${memc_SRC}/mem/ast/visitor/Decorate.cpp
	${memc_SRC}/mem/ast/visitor/FindClasses.cpp
	${memc_SRC}/mem/ast/visitor/FindEntryPoint.cpp
	${memc_SRC}/mem/ast/visitor/FindUse.cpp
	${memc_SRC}/mem/ast/visitor/Prechecker.cpp
	${memc_SRC}/mem/ast/visitor/TopTypesChecker.cpp
	${memc_SRC}/mem/ast/visitor/TypeChecker.cpp
	${memc_SRC}/mem/ast/visitor/TypeMatch.cpp
	${memc_SRC}/mem/ast/visitor/UseAlias.cpp
	${memc_SRC}/mem/ast/visitor/Visitor.cpp
	${memc_SRC}/mem/ast/visitor/XmlDumper.cpp
	${memc_SRC}/mem/codegen/llvm/Codegen.cpp
	${memc_SRC}/mem/codegen/llvm/TypeMaker.cpp
	${memc_SRC}/mem/decorator/External.cpp
	${memc_SRC}/mem/decorator/Overriding.cpp
	${memc_SRC}/mem/decorator/Require.cpp
	${memc_SRC}/mem/decorator/Virtual.cpp
	${memc_SRC}/mem/dep/Dep.cpp
	${memc_SRC}/mem/dep/Tree.cpp
	${memc_SRC}/mem/fs/File.cpp
	${memc_SRC}/mem/fs/FileManager.cpp
	${memc_SRC}/mem/fs/position/Composite.cpp
	${memc_SRC}/mem/fs/position/Cursor.cpp
	${memc_SRC}/mem/fs/position/Position.cpp
	${memc_SRC}/mem/fs/position/Range.cpp
	${memc_BUILT}/mem/lang/Bison.cpp
	${memc_SRC}/mem/lang/Tokenizer.cpp
	${memc_SRC}/mem/log/ConsoleFormatter.cpp
	${memc_SRC}/mem/log/ConsoleLogger.cpp
	${memc_SRC}/mem/log/Formatter.cpp
	${memc_SRC}/mem/log/Logger.cpp
	${memc_SRC}/mem/log/Message.cpp
	${memc_SRC}/mem/log/XmlFormatter.cpp
	${memc_SRC}/mem/opt/Option.cpp
	${memc_SRC}/mem/opt/Options.cpp
	${memc_SRC}/mem/st/Alias.cpp
	${memc_SRC}/mem/st/Arg.cpp
	${memc_SRC}/mem/st/ArrayType.cpp
	${memc_SRC}/mem/st/Class.cpp
	${memc_SRC}/mem/st/Constant.cpp
	${memc_SRC}/mem/st/CoreTypes.cpp
	${memc_SRC}/mem/st/EnumType.cpp
	${memc_SRC}/mem/st/Field.cpp
	${memc_SRC}/mem/st/Func.cpp
	${memc_SRC}/mem/st/FunctionType.cpp
	${memc_SRC}/mem/st/IntConstant.cpp
	${memc_SRC}/mem/st/IntType.cpp
	${memc_SRC}/mem/st/Macro.cpp
	${memc_SRC}/mem/st/Namespace.cpp
	${memc_SRC}/mem/st/Null.cpp
	${memc_SRC}/mem/st/Path.cpp
	${memc_SRC}/mem/st/PrimitiveType.cpp
	${memc_SRC}/mem/st/PointerType.cpp
	${memc_SRC}/mem/st/Symbol.cpp
	${memc_SRC}/mem/st/SymbolTable.cpp
	${memc_SRC}/mem/st/TupleType.cpp
	${memc_SRC}/mem/st/Type.cpp
	${memc_SRC}/mem/st/util.cpp
	${memc_SRC}/mem/st/Var.cpp
	${memc_SRC}/mem/st/VoidType.cpp
	${memc_SRC}/mem/st/visitor/DepBuilder.cpp
	${memc_SRC}/mem/st/visitor/XmlDumper.cpp
	${memc_SRC}/mem/st/visitor/Visitor.cpp
	${memc_SRC}/mem/tool/CommandChain.cpp
	${memc_SRC}/mem/tool/Toolbox.cpp)

# Configuration file

set(memc_VERSION_MAJOR 0)
set(memc_VERSION_MINOR 0)
set(memc_VERSION_PATCH 1)
set(memc_VERSION "${memc_VERSION_MAJOR}.${memc_VERSION_MINOR}.${memc_VERSION_PATCH}")

configure_file(${memc_SRC}/config.h.in ${memc_BUILT}/config.h)

include_directories(${memc_SRC} ${memc_BUILT})
add_executable(memc ${memc_SOURCES})
target_link_libraries(memc dl ${LLVM_LIBS})
