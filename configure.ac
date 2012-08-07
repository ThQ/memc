AC_INIT([memc], [0.1.0], [https://github.com/thomas-quemard/memc/issues/new])
AM_INIT_AUTOMAKE([1.10 foreign no-define])
AC_CONFIG_HEADERS([src/config.h])
AC_CHECK_PROGS(llvm, [llvm-config llvm-config-3.0])
AC_SUBST(LLVM_CPPFLAGS, $($llvm --cppflags))
AC_SUBST(LLVM_LDADD, $($llvm --ldflags --libs native codegen | tr '\n' ' '))
CPPFLAGS="-D __STDC_LIMIT_MACROS=1 -D __STDC_CONSTANT_MACROS=1"
AM_PATH_PYTHON(,,[:])
AM_PROG_CC_C_O
# Search for libdl (Ubuntu requires explicity linking against it)
AC_SEARCH_LIBS([dlopen], [dl dld])
AC_PROG_CXX
AC_PROG_YACC
AC_CONFIG_FILES([ Makefile ])
AC_OUTPUT
