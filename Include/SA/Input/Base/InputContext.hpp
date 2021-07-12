// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_CONTEXT_GUARD
#define SAPPHIRE_INPUT_INPUT_CONTEXT_GUARD

#include <SA/Config.hpp>

#include <SA/Input/Base/Key/InputKeyContext.hpp>
#include <SA/Input/Base/Axis/InputAxisContext.hpp>

namespace Sa
{
	class InputContext
	{
	public:
		enum class ProcessMode
		{
			Consume = 1,
			Forward,
		};

		ProcessMode mode = ProcessMode::Consume;

		InputKeyContext key;
		InputAxisContext axis;

		bool bEnabled = true;

		bool Process(const InputKey& _inKey);
		bool Process(const InputAxis& _inAxis);
	};
}

#endif // GUARD
