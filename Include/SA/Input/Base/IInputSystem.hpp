// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_SYSTEM_GUARD
#define SAPPHIRE_INPUT_INPUT_SYSTEM_GUARD

#include <vector>

#include <SA/Core/Types/Interface.hpp>

#include <SA/Input/Base/Contexts/InputContext.hpp>

namespace Sa
{
	class IInputSystem : public Interface
	{
		std::vector<InputContext*> mContexts;

	public:
		SA_ENGINE_API virtual ~IInputSystem();

		SA_ENGINE_API InputContext* CreateContext();
		SA_ENGINE_API void DestroyContext(InputContext* _context);

		void Clear();

		template <typename InputT>
		bool Process(const InputT& _input);

		virtual void Update() = 0;
	};
}

#include <SA/Input/Base/IInputSystem.inl>

#endif // GUARD
