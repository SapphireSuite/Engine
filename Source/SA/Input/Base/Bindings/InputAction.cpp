// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Bindings/InputAction.hpp>

namespace Sa
{
	InputAction::InputAction(Function<void()> _handle) : mHandle{ std::move(_handle) }
	{
	}


	bool InputAction::Execute(KeyState _keyState)
	{
		(void)_keyState;

		mHandle.Execute();

		return true;
	}

	bool InputAction::Execute(float _value)
	{
		(void)_value;

		mHandle.Execute();

		return true;
	}
}
