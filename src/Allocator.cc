#include <Cor/Allocator.hh>

#include <new>

#include <Cor/Bit.hh>

namespace cor
{
	void ReportAllocatorEvent
	(
		FAllocator* pAlloc,
		void* pOldMemory,
		void* pMemory,
		U64	OldNumBytes,
		U64 NewNumBytes,
		U64 Alignment,
		EAllocatorEventType Type)
	{
		if (!pAlloc->Callbacks.pfnEvent)
			return;

		FAllocatorEvent Event
		{
			pAlloc,
			pOldMemory,
			pMemory,
			OldNumBytes,
			NewNumBytes,
			Alignment,
			Type
		};

		pAlloc->Callbacks.pfnEvent
		(
			pAlloc->Callbacks.pContext,
			&Event
		);
	}
}

void* cor::Allocate
(
	FAllocator* pAlloc,
	U64			NumBytes,
	U64			Alignment)
{
	pAlloc = ResolveAllocator(pAlloc);
	if (!IsValidAllocator(pAlloc) || !NumBytes || !IsPowerOfTwo(Alignment))
		return nullptr;

	void* const pMemory = pAlloc->pfnAllocate
	(
		pAlloc->pContext,
		NumBytes,
		Alignment
	);

	if (pMemory != nullptr)
	{
		ReportAllocatorEvent
		(
			pAlloc,
			nullptr,
			pMemory,
			0u,
			NumBytes,
			Alignment,
			EAllocatorEventType::Allocate
		);
	}

	return pMemory;
}

void* cor::Reallocate
(
	FAllocator* pAlloc,
	void* pMemory,
	U64 OldNumBytes,
	U64 NewNumBytes,
	U64 NewAlignment)
{
	pAlloc = ResolveAllocator(pAlloc);
	if (!IsValidAllocator(pAlloc) || !IsPowerOfTwo(NewAlignment))
		return nullptr;
	if (!(pMemory || NewNumBytes))
		return nullptr;

	void* const pNewMemory = pAlloc->pfnReallocate
	(
		pAlloc->pContext,
		pMemory,
		OldNumBytes,
		NewNumBytes,
		NewAlignment
	);

	if (pNewMemory || !NewNumBytes)
	{
		ReportAllocatorEvent
		(
			pAlloc,
			pMemory,
			pNewMemory,
			OldNumBytes,
			NewNumBytes,
			NewAlignment,
			EAllocatorEventType::Reallocate
		);
	}

	return pNewMemory;
}

void cor::Deallocate
(
	FAllocator* pAlloc,
	void* pMemory)
{
	if (!pMemory)
		return;

	pAlloc = ResolveAllocator(pAlloc);
	if (!IsValidAllocator(pAlloc))
		return;

	ReportAllocatorEvent
	(
		pAlloc,
		pMemory,
		nullptr,
		0,
		0,
		0,
		EAllocatorEventType::Deallocate
	);

	pAlloc->pfnDeallocate(pAlloc->pContext, pMemory);
}

