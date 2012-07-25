AUTOMAKE_OPTIONS = subdir-objects

src_mem = \
 src/mem/Compiler.cpp \
 src/mem/Metadata.cpp \
 src/mem/number.cpp \
 src/mem/Util.cpp
src_mem_ast = \
 src/mem/ast/util.cpp
src_mem_ast_node = \
 src/mem/ast/node/Array.cpp \
 src/mem/ast/node/BinaryExpression.cpp \
 src/mem/ast/node/BinaryOp.cpp \
 src/mem/ast/node/Block.cpp \
 src/mem/ast/node/BracketOp.cpp \
 src/mem/ast/node/Call.cpp \
 src/mem/ast/node/Class.cpp \
 src/mem/ast/node/Dot.cpp \
 src/mem/ast/node/Field.cpp \
 src/mem/ast/node/File.cpp \
 src/mem/ast/node/FinalId.cpp \
 src/mem/ast/node/Func.cpp \
 src/mem/ast/node/If.cpp \
 src/mem/ast/node/Kind.cpp \
 src/mem/ast/node/New.cpp \
 src/mem/ast/node/Node.cpp \
 src/mem/ast/node/NodeValidator.cpp \
 src/mem/ast/node/Number.cpp \
 src/mem/ast/node/Primitive.cpp \
 src/mem/ast/node/Return.cpp \
 src/mem/ast/node/Root.cpp \
 src/mem/ast/node/Text.cpp \
 src/mem/ast/node/Type.cpp \
 src/mem/ast/node/Use.cpp \
 src/mem/ast/node/VarAssign.cpp \
 src/mem/ast/node/VarDecl.cpp \
 src/mem/ast/node/While.cpp
src_mem_ast_visitor = \
 src/mem/ast/visitor/BlockTypesChecker.cpp \
 src/mem/ast/visitor/CheckValidity.cpp \
 src/mem/ast/visitor/FindClasses.cpp \
 src/mem/ast/visitor/FindEntryPoint.cpp \
 src/mem/ast/visitor/FindUse.cpp \
 src/mem/ast/visitor/Prechecker.cpp \
 src/mem/ast/visitor/TopTypesChecker.cpp \
 src/mem/ast/visitor/TypeChecker.cpp \
 src/mem/ast/visitor/TypeMatch.cpp \
 src/mem/ast/visitor/Visitor.cpp \
 src/mem/ast/visitor/XmlDumper.cpp
src_mem_codegen_llvm = \
 src/mem/codegen/llvm/Codegen.cpp
src_mem_dep = \
 src/mem/dep/Dep.cpp \
 src/mem/dep/Tree.cpp
src_mem_fs = \
 src/mem/fs/File.cpp \
 src/mem/fs/FileManager.cpp
src_mem_fs_position = \
 src/mem/fs/position/Composite.cpp \
 src/mem/fs/position/Cursor.cpp \
 src/mem/fs/position/Position.cpp \
 src/mem/fs/position/Range.cpp
src_mem_lang = \
 src/mem/lang/Bison.ypp \
 src/mem/lang/Tokenizer.cpp
src_mem_log = \
 src/mem/log/ConsoleFormatter.cpp \
 src/mem/log/ConsoleLogger.cpp \
 src/mem/log/errors.errors-in \
 src/mem/log/Formatter.cpp \
 src/mem/log/Logger.cpp \
 src/mem/log/Message.cpp
src_mem_opt = \
 src/mem/opt/Option.cpp \
 src/mem/opt/Options.cpp
src_mem_st = \
 src/mem/st/Arg.cpp \
 src/mem/st/Array.cpp \
 src/mem/st/Class.cpp \
 src/mem/st/Field.cpp \
 src/mem/st/Func.cpp \
 src/mem/st/Namespace.cpp \
 src/mem/st/Path.cpp \
 src/mem/st/Primitive.cpp \
 src/mem/st/Ptr.cpp \
 src/mem/st/Symbol.cpp \
 src/mem/st/SymbolTable.cpp \
 src/mem/st/Type.cpp \
 src/mem/st/Util.cpp \
 src/mem/st/Var.cpp
src_mem_st_visitor = \
 src/mem/st/visitor/DepBuilder.cpp \
 src/mem/st/visitor/XmlDumper.cpp \
 src/mem/st/visitor/Visitor.cpp

BUILT_SOURCES = \
 src/mem/lang/Bison.hpp \
 src/mem/lang/TokenKind.hpp \
 src/mem/ast/node/Kind.cpp \
 src/mem/log/errors.hpp


###############################################################################
# Custom rules
###############################################################################

# <fix>
# This is needed by ArchLinux and FreeBSD : otherwise they will complain that
# there is no rule to build Bison.hpp
src/mem/lang/Bison.hpp src/mem/lang/Bison.cpp: src/mem/lang/Bison.ypp
	$(YACC) -d src/mem/lang/Bison.ypp -o src/mem/lang/Bison.cpp
# </fix>

src/mem/log/errors.hpp:
	$(PYTHON) utils/GenErrorClasses.py src/mem/log/errors.errors-in \
		src/mem/log/errors.hpp

src/mem/ast/node/Kind.cpp :
	$(PYTHON) utils/GenNodeTypes.py src/mem/ast/node/Kind.kind-in \
		src/mem/ast/node/Kind.hpp

src/mem/lang/TokenKind.hpp: src/mem/lang/Bison.hpp
	$(PYTHON) utils/GenTokenKind.py src/mem/lang/Bison.hpp \
		src/mem/lang/TokenKind.hpp


###############################################################################
# Programs
###############################################################################

bin_PROGRAMS = mem_compile

#------------------------------------------------------------------------------
# mem-compile
#------------------------------------------------------------------------------
mem_compile_SOURCES =  \
 bin/mem-compile/main.cpp \
 $(src_mem) \
 $(src_mem_ast) \
 $(src_mem_ast_dumper) \
 $(src_mem_ast_node) \
 $(src_mem_ast_visitor) \
 $(src_mem_codegen) \
 $(src_mem_codegen_llvm) \
 $(src_mem_dep) \
 $(src_mem_fs) \
 $(src_mem_fs_position) \
 $(src_mem_lang) \
 $(src_mem_log) \
 $(src_mem_opt) \
 $(src_mem_st) \
 $(src_mem_st_visitor)
mem_compile_LDADD = $(LLVM_LDADD)
mem_compile_CPPFLAGS=$(LLVM_CPPFLAGS) -UNDEBUG
