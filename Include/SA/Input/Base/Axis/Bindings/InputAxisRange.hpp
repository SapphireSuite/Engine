// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_AXIS_RANGE_GUARD
#define SAPPHIRE_INPUT_INPUT_AXIS_RANGE_GUARD

#include <SA/Input/Base/Bindings/InputRangeBase.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisBinding.hpp>

namespace Sa
{
	class InputAxisRange : public InputRangeBase<InputAxisBinding>
	{
	public:
		float minThreshold = 0.0f;
		float maxThreshold = 1.0f;

		float scale = 1.0f;

		using InputRangeBase<InputAxisBinding>::InputRangeBase;

		SA_ENGINE_API bool Execute(float _value) override final;
	};
}

#endif // GUARD
