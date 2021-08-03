// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_SURFACE_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_SURFACE_GUARD

#include <SA/Render/Base/ARenderSurface.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class RenderInstance;

	class RenderSurface : public ARenderSurface
	{
		VkSurfaceKHR mHandle = VK_NULL_HANDLE;

	public:
		RenderSurface(VkSurfaceKHR _handle) noexcept;

		SA_ENGINE_API void Create(const RenderInstance& _inst);
		SA_ENGINE_API void Destroy(const RenderInstance& _inst);


		operator VkSurfaceKHR() const noexcept;
	};
}

#endif

#endif // GUARD
