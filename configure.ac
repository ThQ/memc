AC_INIT([memc], [1.0], [https://github.com/thomas-quemard/memc/issues/new])
AM_INIT_AUTOMAKE([1.10 foreign no-define])
AC_CONFIG_HEADERS([src/config.h])
AC_SUBST(LLVM_CPPFLAGS, $(llvm-config-3.0 --cppflags))
AC_SUBST(LLVM_LDADD, $(llvm-config-3.0 --ldflags --libs nativecodegen | tr '\n' ' '))
CPPFLAGS="-D __STDC_LIMIT_MACROS=1 -D __STDC_CONSTANT_MACROS=1 -O0"
AM_PATH_PYTHON(,,[:])
AM_PROG_CC_C_O
#AC_PROG_CC
AC_PROG_CXX
AC_PROG_YACC
AC_PROG_LEX
AC_CONFIG_FILES([ Makefile ])
AC_OUTPUT
