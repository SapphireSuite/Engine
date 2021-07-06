// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_ACTION_GUARD
#define SAPPHIRE_INPUT_INPUT_ACTION_GUARD

#include <SA/Input/Base/Bindings/InputKeyBinding.hpp>
#include <SA/Input/Base/Bindings/InputAxisBinding.hpp>

#include <SA/Core/Types/Variadics/Function.hpp>

namespace Sa
{
	template <typename BaseT>
	class InputActionBase : public BaseT
	{
	protected:
		Function<void()> mHandle;

	public:
		InputActionBase(Function<void()> _handle) : mHandle{ std::move(_handle) }
		{
		}
	};


	class InputKeyAction : public InputActionBase<InputKeyBinding>
	{
	public:
		using InputActionBase<InputKeyBinding>::InputActionBase;

		SA_ENGINE_API bool Execute(KeyState _keyState) override final;
	};


	class InputAxisAction : public InputActionBase<InputAxisBinding>
	{
	public:
		bool bUseAbs = false;
		float threshold = 0.0f;

		using InputActionBase<InputAxisBinding>::InputActionBase;

		SA_ENGINE_API bool Execute(float _value) override final;
	};
}

#endif // GUARD
