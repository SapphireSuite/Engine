// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_KEY_GUARD
#define SAPPHIRE_INPUT_INPUT_KEY_GUARD

#include <functional> // std::hash

#include <SA/Config.hpp>

#include <SA/Input/Base/Types/InputBase.hpp>

#include <SA/Input/Base/Key.hpp>
#include <SA/Input/Base/KeyState.hpp>

namespace Sa
{
	struct InputRawKey
	{
		Key key = Key::Esc;
		KeyState state = KeyState::Pressed;

		SA_ENGINE_API bool operator==(const InputRawKey& _rhs) const noexcept;
	};


	class InputKey : public InputBase
	{
	public:
		Key key = Key::Esc;
		Flags<KeyState> stateFlags = KeyState::Pressed;

		InputKey() = default;
		InputKey(const InputRawKey& _inRawKey) noexcept;
		SA_ENGINE_API InputKey(Key _key, Flags<KeyState> _stateFlags) noexcept;
	};
}


/// \cond Internal

namespace std
{
	template<>
	struct hash<Sa::InputRawKey>
	{
		SA_ENGINE_API std::size_t operator()(Sa::InputRawKey const& _inKey) const noexcept;
	};
}

/// \endcond


#endif // GUARD
