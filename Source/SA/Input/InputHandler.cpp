// Copyright 2020 Sapphire development team. All Rights Reserved.

#include <Input/InputHandler.hpp>

namespace Sa
{
	bool InputHandler::IsKeyUp(InputKey _key) const
	{
		uint16 index = static_cast<uint16>(_key);
		SA_ASSERT(OutOfRange, SA/Input, index, 0u, (uint16)InputKey::Max);

		return mStates[index] == InputKeyState::Released;
	}

	bool InputHandler::IsKeyDown(InputKey _key) const
	{
		uint16 index = static_cast<uint16>(_key);
		SA_ASSERT(OutOfRange, SA/Input, index, 0u, (uint16)InputKey::Max);

		return mStates[index] == InputKeyState::Pressed || mStates[index] == InputKeyState::Hold;
	}

	void InputHandler::UpdateKey(InputKey _key, InputKeyState _state)
	{
		uint16 index = static_cast<uint16>(_key);
		SA_ASSERT(OutOfRange, SA/Input, index, 0u, (uint16)InputKey::Max);

		if (mStates[index] != _state)
		{
			mStates[index] = _state;
			onKey(_key, _state);
		}
	}
}
