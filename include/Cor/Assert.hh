#pragma once

#include <cstdio>

#include <Cor/Defines.hh>

#define COR_ASSERT( bCond, ... ) \
	if (!(bool)(bCond)) { \
		printf("Assertion violated in " COR_XSTR(__FILE__) " at line " COR_XSTR(__LINE__) ":\n"); \
		printf(#bCond " is false \n"); \
		printf("\n"); \
		COR_DEBUGBREAK; \
	}

#define COR_ASSERT_OR_RETURN( bCond, ... ) \
	if (!(bool)(bCond)) { \
		printf("Assertion violated in " COR_XSTR(__FILE__) " at line " COR_XSTR(__LINE__) ":\n"); \
		printf(#bCond " is false \n"); \
		printf("\n"); \
		COR_DEBUGBREAK; \
		return false; \
	}