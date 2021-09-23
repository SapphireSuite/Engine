// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_KEY_RANGE_GUARD
#define SAPPHIRE_INPUT_INPUT_KEY_RANGE_GUARD

#include <SA/Input/Base/Bindings/InputRangeBase.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyBinding.hpp>

namespace Sa
{
	class InputKeyRange : public InputRangeBase<InputKeyBinding>
	{
	public:
		float scale = 1.0f;

		using InputRangeBase<InputKeyBinding>::InputRangeBase;

		bool Execute(KeyState _keyState) override final;
	};
}

#endif // GUARD
