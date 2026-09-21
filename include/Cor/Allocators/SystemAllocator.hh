#pragma once

#include <Cor/Allocator.hh>

namespace cor
{
	FAllocator* GetSystemAllocator();

	void InitializeSystemAllocator
	(
		FAllocator* pAllocator,
		FAllocatorCallbacks const* pCallbacks
	);
}