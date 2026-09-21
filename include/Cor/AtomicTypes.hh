#pragma once

#include <atomic>

#include <Cor/BaseTypes.hh>

namespace cor
{
	template<typename T>
	struct TAtomic
	{
		TAtomic() : Value(T{ }) {}
		explicit TAtomic(T InitialValue) : Value(InitialValue) {}

		TAtomic(TAtomic const&) = delete;
		TAtomic& operator=(TAtomic const&) = delete;

		std::atomic<T> Value;
	};

	typedef TAtomic<I32> FAtomic32;
	typedef TAtomic<I64> FAtomic64;
}