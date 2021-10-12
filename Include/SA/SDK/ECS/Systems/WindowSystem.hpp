// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_WINDOW_SYSTEM_GUARD
#define SAPPHIRE_SDK_WINDOW_SYSTEM_GUARD

#include <SA/Core/Support/API/GLFW.hpp>

#if SA_GLFW

	#include <SA/Window/GLFW/GLFWWindowInterface.hpp>

#endif

namespace Sa
{
	class WindowSystem
	{
		AWindowInterface* mInterface = nullptr;

	public:
		AWindowInterface* GetInterface() const noexcept;

		template <typename IntfT>
		void Create();

		void Destroy();
	};
}

#include <SA/SDK/ECS/Systems/WindowSystem.inl>

#endif // GUARD
