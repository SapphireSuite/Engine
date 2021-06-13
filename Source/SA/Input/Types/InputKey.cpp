// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Types/InputKey.hpp>

namespace Sa
{
	InputKey::InputKey(Key _key, KeyState _state) noexcept :
		key{ _key },
		state{ _state }
	{
	}


	bool InputKey::operator==(const InputKey& _rhs) const noexcept
	{
		return key == _rhs.key && state == _rhs.state;
	}
	
	bool InputKey::operator!=(const InputKey& _rhs) const noexcept
	{
		return !(*this == _rhs);
	}
}


namespace std
{
	std::size_t hash<Sa::InputKey>::operator()(Sa::InputKey const& _inKey) const noexcept
	{
		std::size_t h = 0;

		h ^= hash<Sa::uint32>{}(static_cast<Sa::uint32>(_inKey.key));
		h ^= hash<Sa::uint32>{}(static_cast<Sa::uint32>(_inKey.state)) << 1;

		return h;
	}
}