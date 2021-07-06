// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Bindings/InputRange.hpp>

namespace Sa
{
	bool InputKeyRange::Execute(KeyState _keyState)
	{
		(void)_keyState;

		mHandle.Execute(scale);

		return true;
	}


	bool InputAxisRange::Execute(float _value)
	{
		// Apply scale.
		_value *= scale;

		const float absV = std::abs(_value);

		// Out of threshold.
		if (absV < minThreshold || absV > maxThreshold)
			return false;

		mHandle.Execute(_value);

		return true;
	}
}
