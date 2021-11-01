// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_CAST_GUARD
#define SAPPHIRE_CORE_CAST_GUARD

#include <type_traits>

#include <SA/Core/Debug.hpp>

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

		SA_ASSERT(Nullptr, SA/Core, casted);

		return *casted;
	}

	template <typename T, typename TIn>
	const T& CastRef(const TIn* _in)
	{
		const T* const casted = Cast<T>(_in);

		SA_ASSERT(Nullptr, SA/Core, casted);

		return *casted;
	}

//}
}

#endif // GUARD
