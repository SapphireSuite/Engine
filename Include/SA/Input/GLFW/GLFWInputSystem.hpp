// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_INPUT_GLFW_INPUT_SYSTEM_GUARD
#define SAPPHIRE_INPUT_GLFW_INPUT_SYSTEM_GUARD

#include <SA/API/GLFW.hpp>

#include <SA/Input/Base/IInputSystem.hpp>

#if SA_GLFW

namespace Sa
{
	class GLFWInputSystem : public IInputSystem
	{
	public:
		SA_ENGINE_API void Update() override final;
	};
}

#endif

#endif // GUARD
