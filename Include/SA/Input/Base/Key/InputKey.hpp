// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_KEY_GUARD
#define SAPPHIRE_INPUT_INPUT_KEY_GUARD

#include <functional> // std::hash

#include <SA/Config.hpp>

#include <SA/Input/Base/InputBase.hpp>

#include <SA/Input/Base/Key/Key.hpp>
#include <SA/Input/Base/Key/KeyState.hpp>

namespace Sa
{
	struct InputKey : public InputBase
	{
		Key key = Key::Esc;
		KeyState state = KeyState::Pressed;

		InputKey() = default;
		SA_ENGINE_API InputKey(Key _key, KeyState _state) noexcept;

		SA_ENGINE_API bool operator==(const InputKey& _rhs) const noexcept;
	};
}


/// \cond Internal

namespace std
{
	template<>
	struct hash<Sa::InputKey>
	{
		SA_ENGINE_API std::size_t operator()(Sa::InputKey const& _inKey) const noexcept;
	};
}

/// \endcond


#endif // GUARD
