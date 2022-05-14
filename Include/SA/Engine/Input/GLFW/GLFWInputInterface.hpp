// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_GLFW_INPUT_INTERFACE_GUARD
#define SAPPHIRE_ENGINE_GLFW_INPUT_INTERFACE_GUARD

#include <SA/Engine/Input/Base/AInputInterface.hpp>
#include <SA/Engine/Input/GLFW/GLFWInputWindowContext.hpp>

#include <SA/Engine/HI/InterfaceList.hpp>

namespace SA::GLFW
{
	class InputInterface : public AInputInterface
	{
		InterfaceList<InputWindowContext> mInputWinContexts;

	public:
		void Create() override final;
		void Destroy() override final;

		void Clear() override final;


		void Update() override final;


		AInputWindowContext* CreateInputWindowContext(AWindow* _win) override final;
		void DestroyInputWindowContext(AInputWindowContext* _winContext) override final;
	};
}

#endif // GUARD
