// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Types/InputAxis.hpp>

#include <Core/Types/Int.hpp>

namespace Sa
{
	InputAxis::InputAxis(Axis _axis, float _value) noexcept :
		axis{ _axis },
		value{ _value }
	{
	}


	bool InputAxis::operator==(const InputAxis& _rhs) const noexcept
	{
		// Compare Axis only.
		return axis == _rhs.axis;

		//return axis == _rhs.axis && value == _rhs.value;
	}

	bool InputAxis::operator!=(const InputAxis& _rhs) const noexcept
	{
		return !(*this == _rhs);
	}
}


namespace std
{
	std::size_t hash<Sa::InputAxis>::operator()(Sa::InputAxis const& _inAxis) const noexcept
	{
		std::size_t h = 0;

		// Compare Axis only.
		h ^= hash<Sa::uint32>{}(static_cast<Sa::uint32>(_inAxis.axis));

		//h ^= hash<Sa::uint32>{}(static_cast<Sa::uint32>(_inAxis.value)) << 1;

		return h;
	}
}
