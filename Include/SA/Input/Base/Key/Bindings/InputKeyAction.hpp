// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_KEY_ACTION_GUARD
#define SAPPHIRE_INPUT_INPUT_KEY_ACTION_GUARD

#include <SA/Input/Base/Bindings/InputActionBase.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyBinding.hpp>

namespace Sa
{
	class InputKeyAction : public InputActionBase<InputKeyBinding>
	{
	public:
		using InputActionBase<InputKeyBinding>::InputActionBase;

		bool Execute(KeyState _keyState) override final;
	};
}

#endif // GUARD
