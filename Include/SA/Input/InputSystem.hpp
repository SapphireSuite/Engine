// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_SYSTEM_GUARD
#define SAPPHIRE_INPUT_INPUT_SYSTEM_GUARD

#include <vector>

#include <SA/Input/InputContext.hpp>

namespace Sa
{
	class InputSystem
	{
		std::vector<InputContext*> mContexts;

	public:
		SA_ENGINE_API ~InputSystem();

		SA_ENGINE_API InputContext* CreateContext();
		SA_ENGINE_API void DestroyContext(InputContext* _context);

		void Clear();

		bool Process(const InputKey& _inKey);
		//bool Process(const InputAxis& _inAxis);
		//bool Process(const InputComposite& _inComp);
	};
}

#endif // GUARD
