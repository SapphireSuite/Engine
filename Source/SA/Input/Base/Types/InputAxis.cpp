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
}
