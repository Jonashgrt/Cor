#include "InternalAllocator.hh"

#include <malloc.h>

#include <Cor/BaseTypes.hh>
#include <Cor/Defines.hh>

namespace cor
{
	void* SystemAllocate
	(
		void*,
		U64 NumBytes,
		U64 Alignment)
	{
		return _aligned_malloc(NumBytes, Alignment);
	}

	void* SystemReallocate
	(
		void*,
		void* pMemory,
		U64 OldNumBytes,
		U64 NewNumBytes,
		U64 NewAlignment)
	{
		COR_UNUSED(OldNumBytes);

		if (!NewNumBytes)
		{
			_aligned_free(pMemory);
			return nullptr;
		}

		if (!pMemory)
			return _aligned_malloc
			(
				NewNumBytes,
				NewAlignment
			);

		return _aligned_realloc
		(
			pMemory,
			NewNumBytes,
			NewAlignment
		);
	}

	void SystemDeallocate(void*, void* pMemory)
	{
		_aligned_free(pMemory);
	}

	FAllocator gSystemAllocator
	{
		nullptr,
		SystemAllocate,
		SystemReallocate,
		SystemDeallocate,
		{ },
		"SystemAllocator",
		nullptr
	};
	
	FAllocator* GetSystemAllocator()
	{
		return &gSystemAllocator;
	}

	void InitializeSystemAllocator
	(
		FAllocator* pAllocator,
		FAllocatorCallbacks const* pCallbacks)
	{
		InitializeAllocatorInterface
		(
			pAllocator,
			nullptr,
			SystemAllocate,
			SystemReallocate,
			SystemDeallocate,
			pCallbacks, 
			"SystemAllocator",
			nullptr
		);
	}
}