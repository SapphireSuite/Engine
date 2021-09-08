// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_GLFW_WINDOW_SYSTEM_GUARD
#define SAPPHIRE_GLFW_WINDOW_SYSTEM_GUARD

#include <SA/Core/Support/API/GLFW.hpp>

#include <SA/Window/Base/AWindowSystem.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	class WindowSystem : public AWindowSystem
	{
	public:
		void Create() override final;
		void Destroy() override final;

		bool QueryRequiredExtensions(std::vector<const char*>& _extensions) const override final;
	};
}

#endif

#endif // GUARD
