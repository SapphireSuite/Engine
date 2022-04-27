// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_AINPUT_WINDOW_CONTEXT_GUARD
#define SAPPHIRE_ENGINE_AINPUT_WINDOW_CONTEXT_GUARD

#include <list>

#include <SA/Engine/HI/HardwareInterfaceBase.hpp>
#include <SA/Engine/Input/Base/InputContext.hpp>

namespace Sa
{
	class AWindow;

	class AInputWindowContext : public HardwareInterfaceBase
	{
		std::list<InputContext> mContexts;

		using HardwareInterfaceBase::Create;

	public:
		/**
		*	Virtual destructor.
		*	Ensure correct polymorphism destruction.
		*/
		virtual ~AInputWindowContext() = default;
		

		virtual void Create(AWindow* _win);

		void Clear() override;


		InputContext* CreateContext();
		bool DestroyContext(const InputContext* _context);
	};
}

#endif // GUARD
