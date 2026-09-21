#pragma once

typedef signed char			I8;
typedef short				I16;
typedef int					I32;
typedef long long			I64;

typedef unsigned char		U8;
typedef unsigned short		U16;
typedef unsigned int		U32;
typedef unsigned long long	U64;

typedef float				F32;
typedef double				F64;

#define I8_MIN		(-127i8 - 1)
#define I16_MIN		(-32767i16 - 1)
#define I32_MIN		(-2147483647i32 - 1)
#define I64_MIN		(-9223372036854775807i64 - 1)

#define I8_MAX		127i8
#define I16_MAX		32767i16
#define I32_MAX		2147483647i32
#define I64_MAX		9223372036854775807i64

#define U8_MAX		0xffui8
#define U16_MAX		0xffffui16
#define U32_MAX		0xffffffffui32
#define U64_MAX		0xffffffffffffffffui64 