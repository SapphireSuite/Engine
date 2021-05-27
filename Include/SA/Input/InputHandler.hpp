// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_HANDLER_GUARD
#define SAPPHIRE_INPUT_INPUT_HANDLER_GUARD

#include <SA/Input/InputKey.hpp>
#include <SA/Input/InputKeyState.hpp>

#include <SA/Core/Types/Variadics/Event.hpp>

namespace Sa
{
	class InputHandler
	{
		InputKeyState mStates[(uint32)InputKey::Max]{ InputKeyState::Released };

	public:
		Event<void(InputKey, InputKeyState)> onKey;

		bool IsKeyUp(InputKey _key) const;
		bool IsKeyDown(InputKey _key) const;

		void UpdateKey(InputKey _key, InputKeyState _state);
	};
}

#endif // GUARD
