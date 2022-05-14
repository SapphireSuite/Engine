// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_GLFW_INPUT_WINDOW_CONTEXT_GUARD
#define SAPPHIRE_ENGINE_GLFW_INPUT_WINDOW_CONTEXT_GUARD

#include <SA/Engine/Input/Base/AInputWindowContext.hpp>

namespace SA::GLFW
{
	class Window;

	class InputWindowContext : public AInputWindowContext
	{
		/// Associated window.
		Window* mWindow = nullptr;

	public:
		void Create(AWindow* _win) override final;
		void Destroy() override final;
	};
}

#endif // GUARD
