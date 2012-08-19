#ifndef _CXX__HPP_
#define _CXX__HPP_

#include "config.h"

#ifdef HAVE_STDINT_H

#include <stdint.h>
typedef uint8_t ui8;
typedef uint16_t ui16;
typedef uint32_t ui32;
typedef uint64_t ui64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#elif defined _MSC_VER

typedef unsigned __int8 ui8;
typedef unsigned __int16 ui16;
typedef unsigned __int32 ui32;
typedef unsigned __int64 ui64;

typedef __int8 i8;
typedef __int16 i16;
typedef __int32 i32;
typedef __int64 i64;

#else
#error "Cannot find fixed size integer types"
#endif


#endif
