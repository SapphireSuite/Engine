// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_RENDER_SYSTEM_GUARD
#define SAPPHIRE_SDK_RENDER_SYSTEM_GUARD

//{ Interface Includes

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

	#include <SA/Render/Vulkan/VkRenderInterface.hpp>

#endif


#include <SA/Core/Support/API/OpenGL.hpp>

#if SA_OPEN_GL

	#include <SA/Render/OpenGL/GLRenderInterface.hpp>

#endif

//}

#include <SA/SDK/ECS/Systems/Render/RenderSubSystem.hpp>

#include <SA/SDK/ECS/Systems/WindowSystem.hpp>

namespace Sa
{
	class WindowSystem;

	class RenderSystem
	{
		ARenderInterface* mInterface = nullptr;

	public:
		ARenderInterface* GetInterface() const noexcept;


		template <typename IntfT>
		IntfT* Create(const WindowSystem& _winSys);

		void Destroy();


		RenderSubSystem* CreateSubSystem(const AGraphicDeviceInfos& _infos);
		void DestroySubSystem(RenderSubSystem* _subSys);
	};
}

#include <SA/SDK/ECS/Systems/Render/RenderSystem.inl>

#endif // GUARD
