#ifndef _MEM__SS__HPP_
#define _MEM__SS__HPP_


#include <assert.h>


#ifndef NDEBUG
#include <stdio.h>
#endif

#define GETTER(name, type) public: type name() const
#define GETTER_REF(name, type) public: type & name()
#define SETTER(name, type) public: void set ## name(type val)

#ifdef NDEBUG
   #define IF_DEBUG if(false)
#endif
#ifndef NDEBUG
   #define IF_DEBUG if(true)
#endif

#ifdef NDEBUG
   #define DEBUG_PRINTF(format, ...)
#endif
#ifndef NDEBUG
   #define DEBUG_PRINTF(format, ...) printf("[ DEBUG ] @%s:%d (%s) ", __FILE__, __LINE__, __FUNCTION__);printf(format, __VA_ARGS__)
#endif

#ifdef NDEBUG
   #define DEBUG_PRINT(str)
#endif
#ifndef NDEBUG
   #define DEBUG_PRINT(str) printf("[ DEBUG ] @%s:%d (%s) %s", __FILE__, __LINE__, __FUNCTION__,  str)
#endif


#ifdef NDEBUG
   #define DEBUG_REQUIRE(cond)
#endif
#ifndef NDEBUG
   #define DEBUG_REQUIRE(cond) assert((cond))
#endif

#ifdef NDEBUG
   #define DEBUG_ENSURE(cond)
#endif
#ifndef NDEBUG
   #define DEBUG_ENSURE(cond) assert((cond))
#endif

#ifdef NDEBUG
   #define DEBUG_DEPRECATED()
#endif
#ifndef NDEBUG
   #define DEBUG_DEPRECATED() printf("%s(...) is deprecated\n", __FUNCTION__);assert(false)
#endif



#ifdef NDEBUG
   #define DEBUG_UNREACHABLE()
#endif
#ifndef NDEBUG
   #define DEBUG_UNREACHABLE() assert(false && "Code point supposed to be unreachable")
#endif

#endif
