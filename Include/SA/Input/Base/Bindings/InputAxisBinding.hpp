// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_AXIS_BINDING_GUARD
#define SAPPHIRE_INPUT_INPUT_AXIS_BINDING_GUARD

#include <SA/Input/Base/Bindings/InputBindingBase.hpp>

namespace Sa
{
	class InputAxisBinding : public InputBindingBase
	{
	public:
		virtual bool Execute(float _value) = 0;
	};
}

#endif // GUARD
