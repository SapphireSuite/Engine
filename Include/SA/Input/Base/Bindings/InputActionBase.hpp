// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_ACTION_BASE_GUARD
#define SAPPHIRE_INPUT_INPUT_ACTION_BASE_GUARD

#include <SA/Core/Types/Variadics/Function.hpp>

namespace Sa
{
	template <typename BaseT>
	class InputActionBase : public BaseT
	{
	protected:
		Function<void()> mHandle;

	public:
		InputActionBase(void(*_func)()) noexcept :
			mHandle{ _func }
		{
		}

		template <typename C>
		InputActionBase(C* _caller, void(C::* _func)()) noexcept :
			mHandle{ _caller, _func }
		{
		}

		InputActionBase(Function<void()> _handle) noexcept :
			mHandle{ std::move(_handle) }
		{
		}
	};
}

#endif // GUARD
