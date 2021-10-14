// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_INPUT_SYSTEM_GUARD
#define SAPPHIRE_SDK_INPUT_SYSTEM_GUARD

#include <SA/Core/Support/API/GLFW.hpp>

#if SA_GLFW

	#include <SA/Input/GLFW/GLFWInputInterface.hpp>

#endif

namespace Sa
{
	class InputSystem
	{
		AInputInterface* mInterface = nullptr;

	public:
		AInputInterface* GetInterface() const noexcept;

		template <typename IntfT>
		IntfT* Create();

		void Destroy();

		void Update();
	};
}

#include <SA/SDK/ECS/Systems/InputSystem.inl>

#endif // GUARD
