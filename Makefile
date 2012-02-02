src_PARSER:=""
src_MEM_PARSER:=`echo src/mem/parser/*.cpp`
src_MEM_AST_NODE:=`echo src/mem/ast/node/*.cpp`
src_MEM_AST_VISITOR:=`echo src/mem/ast/visitor/*.cpp`
src_MEM_AST:=`echo src/mem/ast/*.cpp` ${src_MEM_AST_VISITOR}
src_MEM_FS:=`echo src/mem/fs/*.cpp`
src_MEM_FS_POSITION:=`echo src/mem/fs/position/*.cpp`
src_MEM_LOG:=`echo src/mem/log/*.cpp`
src_MEM_ST:=`echo src/mem/st/*.cpp`
src_MEM_TOKENIZER:=`echo src/mem/tokenizer/*.cpp`
GXX:=clang++ -Wall -pedantic -g -I./src

cppcheck:
	cppcheck --enable=all -q -f src/mem/ast src/mem/fs/ src/mem/log/ src/mem/parser/ src/mem/st/ src/mem/tokenizer/

tokenizer:
	flex -o src/mem/tokenizer/Flex.cpp --header-file=src/mem/tokenizer/Flex.hpp src/mem/grammar/mem.l

parser:
	bison -v --report=all --report-file=bison-report --token-table --debug src/mem/grammar/mem.y -o src/mem/parser/Bison.cpp --defines=src/mem/parser/Bison.hpp

node_types:
	bash process_node_types.sh ./src/mem/parser/NodeTypes.in ./src/mem/parser/NodeTypes.hpp ./src/mem/parser/NodeTypes.cpp

memc: node_types tokenizer parser
	$(GXX) src/mem-compile.c src/mem/Compiler.cpp src/mem/Util.cpp ${src_MEM_AST} ${src_MEM_AST_NODE} ${src_MEM_FS} ${src_MEM_FS_POSITION} ${src_MEM_LOG} ${src_MEM_PARSER} ${src_MEM_TOKENIZER} ${src_MEM_ST} -o build/mem-compile -I./src

thomas_memc: memc
	ln -f ./build/mem-compile ~/bin/

mem-tokenize: node_types tokenizer parser
	${GXX} -o build/mem-tokenize  src/mem-tokenize.c ${src_MEM_AST} ${src_MEM_AST_NODE} ${src_MEM_FS} ${src_MEM_FS_POSITION} ${src_MEM_LOG} ${src_MEM_PARSER} ${src_MEM_TOKENIZER} ${src_MEM_ST}
	ln -f ./build/mem-tokenize ~/bin
