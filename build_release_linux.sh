export CCC_ANALYZER_CPLUSPLUS="true"
export CCC_CXX=`which clang++`

cwd=`pwd`
if [ ! -d "${cwd}/build" ] ; then mkdir "${cwd}/build" ; fi

cd "${cwd}/build"

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS_DEBUG="-Wextra -O2" \
   && make \
   && make test

cd "${cwd}"
