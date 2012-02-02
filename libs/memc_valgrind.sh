valgrind \
	--tool=memcheck \
	--leak-check=full \
	--show-reachable=yes \
	--log-file=valgrind-log \
	--suppressions=valgrind-suppressions \
	../build/mem-compile \
	$1
