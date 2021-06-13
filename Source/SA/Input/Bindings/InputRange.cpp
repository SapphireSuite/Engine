// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Bindings/InputRange.hpp>

namespace Sa
{
	InputRange::InputRange(Function<void(float)> _handle) : mHandle{ std::move(_handle) }
	{
	}


	bool InputRange::Execute(KeyState _keyState)
	{
		(void)_keyState;

		mHandle.Execute(scale);

		return true;
	}

	bool InputRange::Execute(float _value)
	{
		// Apply scale.
		_value *= scale;

		// Out of threshold.
		if (_value < -1.0f + minThreshold || _value > 1.0f - maxThreshold)
			return false;

		mHandle.Execute(_value);

		return true;
	}
}
