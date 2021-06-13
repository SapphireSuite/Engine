// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_CONTEXT_GUARD
#define SAPPHIRE_INPUT_INPUT_CONTEXT_GUARD

#include <unordered_map>

#include <SA/Config.hpp>

#include <SA/Core/Types/Variadics/Function.hpp>

#include <SA/Input/Types/InputAction.hpp>

namespace Sa
{
	class InputContext
	{
		std::unordered_map<InputAction, Function<void()>> mActionMap;

	public:
		bool bEnabled = true;

		SA_ENGINE_API void BindAction(InputAction _action, Function<void()> _func);
		void UnBindAction(InputAction _action);

		bool Process(const InputAction& _action);

		//void BindRange(InputRangeFunc _func);
	};
}

#endif // GUARD
