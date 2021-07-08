// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_RANGE_BASE_GUARD
#define SAPPHIRE_INPUT_INPUT_RANGE_BASE_GUARD

#include <SA/Core/Types/Variadics/Function.hpp>

namespace Sa
{
	template <typename BaseT>
	class InputRangeBase : public BaseT
	{
	protected:
		Function<void(float)> mHandle;

	public:
		InputRangeBase(void(*_func)(float)) noexcept :
			mHandle{ _func }
		{
		}

		template <typename C>
		InputRangeBase(C* _caller, void(C::* _func)(float)) noexcept :
			mHandle{ _caller, _func }
		{
		}

		InputRangeBase(Function<void(float)> _handle) : mHandle{ std::move(_handle) }
		{
		}
	};
}

#endif // GUARD
