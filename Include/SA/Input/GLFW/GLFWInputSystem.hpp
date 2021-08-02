// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_GLFW_INPUT_SYSTEM_GUARD
#define SAPPHIRE_INPUT_GLFW_INPUT_SYSTEM_GUARD

#include <SA/Core/Support/API/GLFW.hpp>

#include <SA/Input/Base/AInputSystem.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	class InputSystem : public AInputSystem
	{
	protected:
		SA_ENGINE_API AInputWindowContext* InstantiateWindowContext() override final;
		SA_ENGINE_API void DeleteWindowContext(AInputWindowContext* _winContext) override final;

	public:
		SA_ENGINE_API void Create() override final;
		SA_ENGINE_API void Destroy() override final;

		SA_ENGINE_API void Update() override final;
	};
}

#endif

#endif // GUARD
