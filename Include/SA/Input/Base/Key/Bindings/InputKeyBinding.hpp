// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_KEY_BINDING_GUARD
#define SAPPHIRE_INPUT_INPUT_KEY_BINDING_GUARD

#include <SA/Input/Base/Bindings/AInputBindingBase.hpp>

#include <SA/Input/Base/Key/KeyState.hpp>

namespace Sa
{
	class InputKeyBinding : public AInputBindingBase
	{
	public:
		virtual bool Execute(KeyState _keyState) = 0;
	};
}

#endif // GUARD
