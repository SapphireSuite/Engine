// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_AXIS_GUARD
#define SAPPHIRE_INPUT_INPUT_AXIS_GUARD

#include <SA/Config.hpp>

#include <SA/Input/Base/InputBase.hpp>
#include <SA/Input/Base/Axis/Axis.hpp>

namespace Sa
{
	class InputAxis : public InputBase
	{
	public:
		Axis axis = Axis::None;
		float value = 0.0f;

		InputAxis(Axis _axis, float _value = 0.0f) noexcept;
	};
}

#endif // GUARD
