// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Types/InputAction.hpp>

namespace Sa
{
	InputAction::InputAction(InputKey _key, InputKeyState _state) :
		key{ _key },
		state{ _state }
	{
	}


	bool InputAction::operator==(const InputAction& _rhs) const
	{
		return key == _rhs.key && state == _rhs.state;
	}

	bool InputAction::operator!=(const InputAction& _rhs) const
	{
		return !(*this == _rhs);
	}
}


namespace std
{
	std::size_t hash<Sa::InputAction>::operator()(Sa::InputAction const& _action) const noexcept
	{
		std::size_t h = 0;

		h ^= hash<Sa::uint32>{}(static_cast<Sa::uint32>(_action.key));
		h ^= hash<Sa::uint32>{}(static_cast<Sa::uint32>(_action.state)) << 1;

		return h;
	}
}
