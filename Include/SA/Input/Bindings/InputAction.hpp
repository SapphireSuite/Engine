// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_ACTION_GUARD
#define SAPPHIRE_INPUT_INPUT_ACTION_GUARD

#include <SA/Input/Bindings/InputBindingBase.hpp>

#include <SA/Core/Types/Variadics/Function.hpp>

namespace Sa
{
	class InputAction : public InputBindingBase
	{
		Function<void()> mHandle;
	
	public:
		SA_ENGINE_API InputAction(Function<void()> _handle);

		bool Execute(KeyState _keyState) override final;
		bool Execute(float _value) override final;
	};
}

#endif // GUARD
