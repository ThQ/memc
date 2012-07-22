#ifndef _MEM__SS__HPP_
#define _MEM__SS__HPP_

#ifndef NDEBUG
#include <stdio.h>
#endif

#define GETTER(name, type) public: type name() const
#define SETTER(name, type) public: void set ## name(type val)

#ifdef NDEBUG
   #define IF_DEBUG if(0)
#endif
#ifndef NDEBUG
   #define IF_DEBUG if(1)
#endif

#ifdef NDEBUG
   #define DEBUG_PRINTF(format, ...)
#endif
#ifndef NDEBUG
   #define DEBUG_PRINTF(format, ...) printf("%s:%d [DEBUG] ", __FILE__, __LINE__);printf(format, __VA_ARGS__)
#endif


#endif
