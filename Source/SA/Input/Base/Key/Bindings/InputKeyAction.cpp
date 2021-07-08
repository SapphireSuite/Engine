// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Key/Bindings/InputKeyAction.hpp>

namespace Sa
{
	bool InputKeyAction::Execute(KeyState _keyState)
	{
		(void)_keyState;

		mHandle.Execute();

		return true;
	}
}
