// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_AXIS_ACTION_GUARD
#define SAPPHIRE_INPUT_INPUT_AXIS_ACTION_GUARD

#include <SA/Input/Base/Bindings/InputActionBase.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisBinding.hpp>

namespace Sa
{
	class InputAxisAction : public InputActionBase<InputAxisBinding>
	{
	public:
		bool bUseAbs = true;
		float threshold = 0.0f;

		using InputActionBase<InputAxisBinding>::InputActionBase;

		bool Execute(float _value) override final;
	};
}

#endif // GUARD
