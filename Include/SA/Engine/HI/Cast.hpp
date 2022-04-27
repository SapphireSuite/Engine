// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_CAST_GUARD
#define SAPPHIRE_ENGINE_CAST_GUARD

#include <type_traits>

#include <SA/Collections/Debug>

namespace Sa
{
//{ Cast

	template <typename T, typename TIn>
	T& Cast(TIn& _in)
	{
		if constexpr (std::is_polymorphic<TIn>::value)
			return dynamic_cast<T&>(_in);
		else
			return static_cast<T&>(_in);
	}

	template <typename T, typename TIn>
	const T& Cast(const TIn& _in)
	{
		if constexpr (std::is_polymorphic<TIn>::value)
			return dynamic_cast<const T&>(_in);
		else
			return static_cast<const T&>(_in);
	}


	template <typename T, typename TIn>
	T* Cast(TIn* _in)
	{
		if constexpr (std::is_polymorphic<TIn>::value)
			return dynamic_cast<T*>(_in);
		else
			return static_cast<T*>(_in);
	}

	template <typename T, typename TIn>
	const T* Cast(const TIn* _in)
	{
		if constexpr (std::is_polymorphic<TIn>::value)
			return dynamic_cast<const T*>(_in);
		else
			return static_cast<const T*>(_in);
	}

//}


//{ Cast Ref

	template <typename T, typename TIn>
	T& CastRef(TIn& _in)
	{
		return Cast<T>(_in);
	}

	template <typename T, typename TIn>
	T& CastRef(TIn* _in)
	{
		T* const casted = Cast<T>(_in);

		SA_ASSERT(Nullptr, SA/HardwareInterface, casted);

		return *casted;
	}

	template <typename T, typename TIn>
	const T& CastRef(const TIn* _in)
	{
		const T* const casted = Cast<T>(_in);

		SA_ASSERT(Nullptr, SA/HardwareInterface, casted);

		return *casted;
	}

//}
}

#endif // GUARD
