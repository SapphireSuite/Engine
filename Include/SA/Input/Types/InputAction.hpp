// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_ACTION_GUARD
#define SAPPHIRE_INPUT_INPUT_ACTION_GUARD

#include <functional> // std::hash

#include <SA/Config.hpp>

#include <SA/Input/InputKey.hpp>
#include <SA/Input/InputKeyState.hpp>

namespace Sa
{
	class InputAction
	{
	public:
		InputKey key = InputKey::Esc;
		InputKeyState state = InputKeyState::Pressed;

		InputAction() = default;
		SA_ENGINE_API InputAction(InputKey _key, InputKeyState _state);


		bool operator==(const InputAction& _rhs) const;
		bool operator!=(const InputAction& _rhs) const;
	};
}


/// \cond Internal

namespace std
{
	template<>
	struct hash<Sa::InputAction>
	{
		std::size_t operator()(Sa::InputAction const& _action) const noexcept;
	};
}

/// \endcond

#endif // GUARD
