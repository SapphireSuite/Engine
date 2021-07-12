// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Key/Bindings/InputKeyRange.hpp>

namespace Sa
{
	bool InputKeyRange::Execute(KeyState _keyState)
	{
		(void)_keyState;

		mHandle.Execute(scale);

		return true;
	}
}
