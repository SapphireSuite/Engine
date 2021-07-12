// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Key/InputKeyBind.hpp>

namespace Sa
{
	InputKeyBind::InputKeyBind(const InputKey& _inRawKey) noexcept :
		key{ _inRawKey.key },
		stateFlags{ _inRawKey.state }
	{
	}

	InputKeyBind::InputKeyBind(Key _key, Flags<KeyState> _stateFlags) noexcept :
		key{ _key },
		stateFlags{ _stateFlags }
	{
	}
}
