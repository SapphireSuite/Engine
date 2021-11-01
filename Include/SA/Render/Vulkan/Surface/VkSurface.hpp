// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SURFACE_GUARD
#define SAPPHIRE_RENDER_VK_SURFACE_GUARD

#include <SA/Render/Base/Surface/ARenderSurface.hpp>

#include <SA/Render/Vulkan/Surface/VkSwapChain.hpp>
#include <SA/Render/Vulkan/Surface/VkSurfaceSupportDetails.hpp>

namespace Sa
{
	struct RenderPassDescriptor;
}

namespace Sa::Vk
{
	class WindowSurface;
	class RenderPass;

	class Surface : public ARenderSurface
	{
		VkSurfaceKHR mHandle = VK_NULL_HANDLE;

		SwapChain mSwapChain;

	public:
		Format GetFormat() const override final;
		bool FrameBuffersValid() const noexcept;


		void Create(const Device& _device, const WindowSurface& _winSurface);
		void Destroy(const Device& _device);

		void CreateFrameBuffers(const Device& _device, const RenderPass& _renderPass, const RenderPassDescriptor& _renderPassDesc);
		void DestroyFrameBuffers(const Device& _device);


		FrameBuffer& Begin(const Device& _device);
		void End(const Device& _device, const std::vector<CommandBuffer>& _cmdBuffers);


		SurfaceSupportDetails QuerySupportDetails(VkPhysicalDevice _device) const;


		operator VkSurfaceKHR() const noexcept;
	};
}

#endif // GUARD
