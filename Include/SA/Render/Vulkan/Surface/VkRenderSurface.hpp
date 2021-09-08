// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_SURFACE_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_SURFACE_GUARD

#include <SA/Render/Base/ARenderSurface.hpp>

#include <SA/Render/Vulkan/Surface/VkSwapChain.hpp>
#include <SA/Render/Vulkan/Surface/VkRenderSurfaceSupportDetails.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class RenderInstance;

	class RenderSurface : public ARenderSurface
	{
		VkSurfaceKHR mHandle = VK_NULL_HANDLE;

		SwapChain mSwapChain;

	public:
		RenderSurface() = default;
		RenderSurface(VkSurfaceKHR _handle) noexcept;

		Format GetFormat() const override final;


		//void Init(const AWindow& _win, );

		void Create(const Device& _device);
		void Destroy(const RenderInstance& _inst, const Device& _device);


		RenderSurfaceSupportDetails QuerySupportDetails(VkPhysicalDevice _device) const;


		operator VkSurfaceKHR() const noexcept;
	};
}

#endif

#endif // GUARD
