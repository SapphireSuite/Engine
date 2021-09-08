// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_AXIS_BIND_GUARD
#define SAPPHIRE_INPUT_INPUT_AXIS_BIND_GUARD

#include <SA/Input/Base/Axis/InputAxis.hpp>

namespace Sa
{
	class InputAxisBind
	{
	public:
		Axis axis;

		InputAxisBind() = default;
		InputAxisBind(Axis _axis) noexcept;
		InputAxisBind(const InputAxis& _inAxis) noexcept;
	};
}

#endif // GUARD
