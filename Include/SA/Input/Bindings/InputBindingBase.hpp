// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_BINDING_BASE_GUARD
#define SAPPHIRE_INPUT_INPUT_BINDING_BASE_GUARD

#include <SA/Input/KeyState.hpp>

namespace Sa
{
	class InputBindingBase
	{
	public:
		virtual ~InputBindingBase() = default;

		virtual bool Execute(KeyState _keyState) = 0;
		virtual bool Execute(float _value) = 0;
	};
}

#endif // GUARD
