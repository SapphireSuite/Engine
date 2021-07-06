// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_RANGE_GUARD
#define SAPPHIRE_INPUT_INPUT_RANGE_GUARD

#include <SA/Input/Base/Bindings/InputBindingBase.hpp>

#include <SA/Core/Types/Variadics/Function.hpp>

namespace Sa
{
	class InputRange : public InputBindingBase
	{
		Function<void(float)> mHandle;

	public:
		float minThreshold = 0.0f;
		float maxThreshold = 0.0f;

		float scale = 1.0f;

		SA_ENGINE_API InputRange(Function<void(float)> _handle);

		bool Execute(KeyState _keyState) override final;
		bool Execute(float _value) override final;
	};
}

#endif // GUARD
