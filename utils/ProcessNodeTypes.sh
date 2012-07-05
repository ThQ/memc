#!/bin/sh

SRC=$1

lineno=0
values=""
names=""
fHPP="$2"
fCPP="$3"
echo $fHPP
while read line ; do
    lineno=$(($lineno+1));
    values="$values"$'\n'"#define MEM_NODE_${line%% *} $lineno"
    names="$names"$'\n'"   , "'"'"${line##* }"'"'
done < $SRC

echo "#ifndef MEM_PARSER_NODE_TYPES" > $fHPP
echo "#define MEM_PARSER_NODE_TYPES" >> $fHPP
echo "$values" >> $fHPP
echo >> $fHPP
echo "namespace mem { namespace parser {" >> $fHPP
echo "extern const char* node_names[];" >> $fHPP
echo "}}" >> $fHPP
echo >> $fHPP
echo "#endif" >> $fHPP

echo '#include "mem/parser/NodeTypes.hpp"' > $fCPP
echo "namespace mem { namespace parser {" >> $fCPP
echo "const char* node_names[] = {"'"'"Unknown"'"' $'\n' >> $fCPP
echo "$names" >> $fCPP
echo "};" >> $fCPP
echo "}}" >> $fCPP
echo >> $fCPP

