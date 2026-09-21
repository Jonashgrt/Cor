#pragma once

#include <Cor/Allocator.hh>

namespace cor
{
	inline void InitializeAllocatorInterface
	(
		FAllocator* pAllocator,
		void* pContext,
		PFNAllocatorAllocate pfnAllocate,
		PFNAllocatorReallocate pfnReallocate,
		PFNAllocatorDeallocate pfnDeallocate,
		FAllocatorCallbacks const* pCallbacks,
		char const* pName = nullptr,
		FAllocator* pParent = nullptr)
	{
		if (!pAllocator)
			return;

		pAllocator->pContext = pContext;
		pAllocator->pfnAllocate = pfnAllocate;
		pAllocator->pfnReallocate = pfnReallocate;
		pAllocator->pfnDeallocate = pfnDeallocate;
		pAllocator->Callbacks = (pCallbacks) ? *pCallbacks : FAllocatorCallbacks{ };
		pAllocator->pName = pName;
		pAllocator->pParent = pParent;
	}
}