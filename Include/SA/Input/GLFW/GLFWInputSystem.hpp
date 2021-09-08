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
		AInputWindowContext* InstantiateWindowContext() override final;
		void DeleteWindowContext(AInputWindowContext* _winContext) override final;

	public:
		void Create() override final;
		void Destroy() override final;

		void Update() override final;
	};
}

#endif

#endif // GUARD
