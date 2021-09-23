// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_KEY_BIND_GUARD
#define SAPPHIRE_INPUT_INPUT_KEY_BIND_GUARD

#include <SA/Config.hpp>

#include <SA/Input/Base/Key/InputKey.hpp>

namespace Sa
{
	class InputKeyBind
	{
	public:
		Key key = Key::Esc;
		Flags<KeyState> stateFlags = KeyState::Pressed;

		InputKeyBind() = default;
		InputKeyBind(const InputKey& _inRawKey) noexcept;
		InputKeyBind(Key _key, Flags<KeyState> _stateFlags) noexcept;
	};
}

#endif // GUARD
