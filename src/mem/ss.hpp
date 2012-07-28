#ifndef _MEM__SS__HPP_
#define _MEM__SS__HPP_


#include <assert.h>


#ifndef NDEBUG
#include <stdio.h>
#endif

#define GETTER(name, type) public: type name() const
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
   #define DEBUG_PRINTF(format, ...) printf("%s:%d [DEBUG] ", __FILE__, __LINE__);printf(format, __VA_ARGS__)
#endif


#endif
