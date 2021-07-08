// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Axis/Bindings/InputAxisAction.hpp>

namespace Sa
{
	bool InputAxisAction::Execute(float _value)
	{
		if (bUseAbs)
			_value = std::abs(_value);

		if (_value >= threshold)
			mHandle.Execute();

		return true;
	}
}
