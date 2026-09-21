#pragma once

#include <atomic>

#include <Cor/Defines.hh>
#include <Cor/AtomicTypes.hh>

namespace cor
{
	template<typename T>
	COR_FORCEINLINE void InitializeAtomic(TAtomic<T>* pAtomic, T Value)
	{
		pAtomic->Value.store(Value, std::memory_order_relaxed);
	}

	template<typename T>
	COR_FORCEINLINE void StoreAtomic
	(
		TAtomic<T>* pAtomic, 
		T Value, 
		std::memory_order Order = std::memory_order_release)
	{
		pAtomic->Value.store(Value, Order);
	}

	template<typename T>
	COR_FORCEINLINE T LoadAtomic
	(
		TAtomic<T> const* pAtomic,
		std::memory_order Order = std::memory_order_acquire)
	{
		return pAtomic->Value.load(Order);
	}

	template<typename T> 
	COR_FORCEINLINE T ExchangeAtomic
	(
		TAtomic<T>* pAtomic,
		T Value,
		std::memory_order Order = std::memory_order_acq_rel)
	{
		return pAtomic->Value.exchange(Value, Order);
	}

	template<typename T>
	inline T CompareExchangeAtomic
	(
		TAtomic<T>* pAtomic,
		T Exchange,
		T Comparand,
		std::memory_order SuccesOrder = std::memory_order_acq_rel,
		std::memory_order FailureOrder = std::memory_order_acquire)
	{
		T Expected = Comparand;
		COR_UNUSED(pAtomic->Value.compare_exchange_strong
		(
			Expected,
			Exchange,
			SuccesOrder,
			FailureOrder
		));
		return Expected;
	}

	template <typename T>
	COR_FORCEINLINE bool CompareExchangeAtomicWeak
	(
		TAtomic<T>* pAtomic,
		T* pExpected,
		T Exchange,
		std::memory_order SuccessOrder,
		std::memory_order FailureOrder)
	{
		return pAtomic->Value.compare_exchange_weak
		(
			*pExpected,
			Exchange,
			SuccessOrder,
			FailureOrder
		);
	}

	template<typename T>
	COR_FORCEINLINE bool CompareExchangeAtomicStrong
	(
		TAtomic<T>* pAtomic,
		T* pExpected,
		T Exchange,
		std::memory_order SuccessOrder,
		std::memory_order FailureOrder)
	{
		return pAtomic->Value.compare_exchange_strong
		(
			*pExpected,
			Exchange,
			SuccessOrder,
			FailureOrder
		);
	}

	template<typename T>
	COR_FORCEINLINE T FetchAddAtomic
	(
		TAtomic<T>* pAtomic,
		T Value,
		std::memory_order Order = std::memory_order_acq_rel)
	{
		return pAtomic->Value.fetch_add(Value, Order);
	}

	template<typename T>
	COR_FORCEINLINE T AddAtomic
	(
		TAtomic<T>* pAtomic,
		T Value,
		std::memory_order Order = std::memory_order_acq_rel)
	{
		return FetchAddAtomic(pAtomic, Value, Order) + Value;
	}

	template<typename T>
	COR_FORCEINLINE T IncrementAtomic
	(
		TAtomic<T>* pAtomic,
		std::memory_order Order = std::memory_order_acq_rel)
	{
		return AddAtomic(pAtomic, T{1}, Order);
	}

	template<typename T>
	COR_FORCEINLINE T FetchSubstractAtomic
	(
		TAtomic<T>* pAtomic,
		T Value,
		std::memory_order Order = std::memory_order_acq_rel)
	{
		return pAtomic->Value.fetch_sub(Value, Order);
	}

	template<typename T>
	COR_FORCEINLINE T DecrementAtomic
	(
		TAtomic<T>* pAtomic,
		std::memory_order Order = std::memory_order_acq_rel)
	{
		return FetchSubstractAtomic(pAtomic, T{1}, Order) - T{1};
	}

	COR_FORCEINLINE void AtomicThreadFence(std::memory_order Order)
	{
		std::atomic_thread_fence(Order);
	}
}