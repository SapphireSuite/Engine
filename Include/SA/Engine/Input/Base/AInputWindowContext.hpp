// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AINPUT_WINDOW_CONTEXT_GUARD
#define SAPPHIRE_ENGINE_AINPUT_WINDOW_CONTEXT_GUARD

#include <forward_list>

#include <SA/Engine/HI/HardwareInterface.hpp>
#include <SA/Engine/Input/Base/InputContext.hpp>

namespace Sa
{
	class AWindow;

	class AInputWindowContext : protected HardwareInterface
	{
		std::forward_list<InputContext> mContexts;

		using HardwareInterface::Create; // overloaded.

	public:
		virtual void Create(AWindow* _win);
		using HardwareInterface::Destroy;

		void Clear() override;


		InputContext* CreateContext();
		bool DestroyContext(const InputContext* _context);
	};
}

#endif // GUARD
