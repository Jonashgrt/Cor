#pragma once

#include <Cor/Defines.hh>
#include <Cor/BaseTypes.hh>

namespace cor
{
	COR_FORCEINLINE constexpr bool IsPowerOfTwo(U64 Value)
	{
		return Value && !(Value & (Value - 1u));
	}

	inline U32 NextPowerOfTwo(U32 Value)
	{
		U32 Result = 1u;
		while (Result < Value && Result <= (U32_MAX / 2u))
			Result <<= 1u;
		return Result;
	}
}