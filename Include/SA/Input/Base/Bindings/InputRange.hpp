// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_RANGE_GUARD
#define SAPPHIRE_INPUT_INPUT_RANGE_GUARD

#include <SA/Input/Base/Bindings/InputKeyBinding.hpp>
#include <SA/Input/Base/Bindings/InputAxisBinding.hpp>

#include <SA/Core/Types/Variadics/Function.hpp>

namespace Sa
{
	template <typename BaseT>
	class InputRangeBase : public BaseT
	{
	protected:
		Function<void(float)> mHandle;

	public:
		InputRangeBase(Function<void(float)> _handle) : mHandle{ std::move(_handle) }
		{
		}
	};


	class InputKeyRange : public InputRangeBase<InputKeyBinding>
	{
	public:
		float scale = 1.0f;

		using InputRangeBase<InputKeyBinding>::InputRangeBase;

		SA_ENGINE_API bool Execute(KeyState _keyState) override final;
	};


	class InputAxisRange : public InputRangeBase<InputAxisBinding>
	{
	public:
		float minThreshold = 0.0f;
		float maxThreshold = 1.0f;

		float scale = 1.0f;

		using InputRangeBase<InputAxisBinding>::InputRangeBase;

		SA_ENGINE_API bool Execute(float _value) override final;
	};
}

#endif // GUARD
