#pragma once

//
/* Platform specific defines */
//

#if defined (_WIN32) || defined(_WIN64) || defined(__WINDOWS__) || defined(__WIN32__)
#define COR_PLATFORM_WINDOWS 
#else
#error "Unsupported platform!"
#endif

//
/* Architecture specific defines */
//

#if defined(COR_PLATFORM_WINDOWS)
#if defined(_WIN64)
#define COR_ARCHITECTURE_64BIT
#else
#error "Unsupported architecture!"
#endif
#endif

#if defined(COR_ARCHITECTURE_64BIT)
#define COR_CACHE_LINE_SIZE 64u
#endif

//
/* Compiler specific defines */
//

#if defined(_MSC_VER)
#define COR_COMPILER_MSVC
#else
#error "Unsupported compiler!"
#endif

#if defined(COR_COMPILER_MSVC)
#define COR_FORCEINLINE __forceinline
#define COR_RESTRICT __restrict
#define COR_DEBUGBREAK __debugbreak()
#endif

//
/* Attributes */
//

#define COR_NODISCARD [[nodiscard]]
#define COR_THREAD_LOCAL thread_local

//
/* Macros */
//

#define COR_ALIGNAS(Alignment) alignas(Alignment)
#define COR_UNUSED(x) (void)(x)

// Stringification
#define COR_STR(s) #s
#define COR_XSTR(s) COR_STR(s)