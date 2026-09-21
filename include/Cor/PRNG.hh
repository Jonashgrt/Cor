#pragma once

#include <Cor/Defines.hh>
#include <Cor/BaseTypes.hh>
#include <Cor/Assert.hh>

namespace cor
{
	// ref: https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp
	COR_FORCEINLINE constexpr U32 XORShift32Seed(U32 SequenceIndex)
	{
		//				GoldenRatio							  MurmurHash3
		const U32 Res = 0x9E3779B9u ^ ((SequenceIndex + 1u) * 0x85EBCA6Bu);
		return Res ? Res : SequenceIndex + 1;
	}

	// ref: https://www.jstatsoft.org/article/view/v008i14/xorshift.pdf
	inline U32 XORShift32Next(U32* pState)
	{
		COR_ASSERT(pState);
		COR_ASSERT(*pState);

		U32 Value = *pState;
		Value ^= Value << 13u;
		Value ^= Value >> 17u;
		Value ^= Value << 5u;

		*pState = Value;
		return Value;
	}
}