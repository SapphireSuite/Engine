// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Bindings/InputAction.hpp>

namespace Sa
{
	bool InputKeyAction::Execute(KeyState _keyState)
	{
		(void)_keyState;

		mHandle.Execute();

		return true;
	}

	bool InputAxisAction::Execute(float _value)
	{
		if (bUseAbs)
			_value = std::abs(_value);

		if(_value >= threshold)
			mHandle.Execute();

		return true;
	}
}
