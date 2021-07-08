// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Types/InputKey.hpp>

namespace Sa
{
	bool InputRawKey::operator==(const InputRawKey& _rhs) const noexcept
	{
		return key == _rhs.key && state == _rhs.state;
	}


	InputKey::InputKey(const InputRawKey& _inRawKey) noexcept :
		key{ _inRawKey.key },
		stateFlags{ _inRawKey.state }
	{
	}

	InputKey::InputKey(Key _key, Flags<KeyState> _stateFlags) noexcept :
		key{ _key },
		stateFlags{ _stateFlags }
	{
	}
}


namespace std
{
	std::size_t hash<Sa::InputRawKey>::operator()(Sa::InputRawKey const& _inKey) const noexcept
	{
		std::size_t h = 0;

		h ^= hash<Sa::uint32>{}(static_cast<Sa::uint32>(_inKey.key));
		h ^= hash<Sa::uint32>{}(static_cast<Sa::uint32>(_inKey.state)) << 1;

		return h;
	}
}