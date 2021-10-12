// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_RENDER_SUB_SYSTEM_GUARD
#define SAPPHIRE_SDK_RENDER_SUB_SYSTEM_GUARD

//{ Interface Includes

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

	#include <SA/Render/Vulkan/VkRenderSubInterface.hpp>

#endif


#include <SA/Core/Support/API/OpenGL.hpp>

#if SA_OPEN_GL

	#include <SA/Render/OpenGL/GLRenderSubInterface.hpp>

#endif

//}

namespace Sa
{
	class ARenderInterface;

	class RenderSubSystem
	{
		ARenderSubInterface* mInterface = nullptr;

	public:
		ARenderSubInterface* GetInterface() const noexcept;

		void Create(ARenderInterface* _mainIntf, const AGraphicDeviceInfos& _infos);
		void Destroy(ARenderInterface* _mainIntf);
	};
}

#endif // GUARD
