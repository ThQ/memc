valgrind \
	--tool=memcheck \
	--leak-check=full \
	--show-reachable=yes \
	--log-file=valgrind-log \
	--suppressions=valgrind-suppressions \
	memc \
	$1 $2 $3
