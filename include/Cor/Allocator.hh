#pragma once

#include <new>
#include <type_traits>

#include <Cor/Fwd.hh>
#include <Cor/BaseTypes.hh>
#include <Cor/Defines.hh>
#include <Cor/Bit.hh>

namespace cor
{
	struct FAllocator;

	enum class EAllocatorEventType : U32
	{
		Allocate,
		Reallocate,
		Deallocate,
		Reset
	};

	struct FAllocatorEvent
	{
		FAllocator* pAlloc;
		void* pOldMem;
		void* pMem;
		U64	OldNumBytes;
		U64	NewNumBytes;
		U64	Alignment;
		EAllocatorEventType Type;
	};

	typedef void (*PFNAllocatorEvent)(void* pContext, FAllocatorEvent const* pEvent);

#define COR_DECLARE_ALLOCATOR_CALLBACK(FuncName) void FuncName(void* pContext, ::cor::FAllocatorEvent const* pEvent)

	struct FAllocatorCallbacks
	{
		void*				pContext;
		PFNAllocatorEvent	pfnEvent;
	};

	typedef void* (*PFNAllocatorAllocate)
	(
		void*	pContext,
		U64		NumBytes,
		U64		Alignment
	);

	typedef void* (*PFNAllocatorReallocate)
	(
		void*	pContext,
		void*	pMemory,
		U64		OldNumBytes,
		U64		NewNumBytes,
		U64		Alignment
	);

	typedef void  (*PFNAllocatorDeallocate)
	(
		void* pContext,
		void* pMemory
	);

	struct FAllocator
	{
		void*					pContext;
		PFNAllocatorAllocate	pfnAllocate;
		PFNAllocatorReallocate	pfnReallocate;
		PFNAllocatorDeallocate	pfnDeallocate;
		FAllocatorCallbacks		Callbacks;
		char const*				pName;
		FAllocator*				pParent;
	};

	void* Allocate
	(
		FAllocator* pAllocator,
		U64			NumBytes,
		U64			Alignment
	);

	void* Reallocate
	(
		FAllocator* pAllocator,
		void* pMemory,
		U64 OldNumBytes,
		U64 NewNumBytes,
		U64 NewAlignment 
	);

	void Deallocate
	(
		FAllocator* pAllocator,
		void* pMemory
	);

	template<typename T>
	inline T* AllocateArray
	(
		FAllocator* pAllocator,
		U64 NumElements,
		U64 Alignment)
	{
		if (NumElements == 0u || Alignment < alignof(T) || !IsPowerOfTwo(Alignment) || NumElements > U64_MAX / sizeof(T))
			return nullptr;

		void* const pStorage = Allocate
		(
			pAllocator,
			sizeof(T) * NumElements,
			Alignment
		);
		if (!pStorage)
			return nullptr;

		T* const pObjects = (T*)pStorage;
		for (U64 Index = 0u; Index < NumElements; ++Index)
			::new ((void*)(pObjects + Index)) T{};
		return pObjects;
	}

	template<typename T>
	inline void DeallocateArray
	(
		FAllocator* pAllocator,
		T* pObjects,
		U64 NumElements)
	{
		if (!pObjects)
			return;

		if constexpr (!std::is_trivially_destructible_v<T>)
		{
			for (U64 Index = NumElements; Index != 0u; --Index)
				pObjects[Index - 1u].~T();
		}
		Deallocate(pAllocator, pObjects);
	}

	FAllocator* GetSystemAllocator();

	COR_FORCEINLINE constexpr FAllocator* ResolveAllocator(FAllocator* pAllocator)
	{
		return ((pAllocator != nullptr) ? pAllocator : GetSystemAllocator());
	}

	inline constexpr bool IsValidAllocator(FAllocator const* pAllocator)
	{
		return	pAllocator
			&& pAllocator->pfnAllocate
			&& pAllocator->pfnReallocate
			&& pAllocator->pfnDeallocate;
	}
}