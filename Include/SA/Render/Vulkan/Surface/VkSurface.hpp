// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SURFACE_GUARD
#define SAPPHIRE_RENDER_VK_SURFACE_GUARD

#include <SA/Render/Base/ARenderSurface.hpp>

#include <SA/Render/Vulkan/Surface/VkSwapChain.hpp>
#include <SA/Render/Vulkan/Surface/VkSurfaceSupportDetails.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Surface : public ARenderSurface
	{
		VkSurfaceKHR mHandle = VK_NULL_HANDLE;

		SwapChain mSwapChain;

	public:
		Surface() = default;
		Surface(VkSurfaceKHR _handle) noexcept;

		Format GetFormat() const override final;


		void Create(const ARenderDevice* _device) override final;
		void Destroy(const ARenderDevice* _device) override final;

		void CreateFrameBuffers(const ARenderDevice* _device, const ARenderPass* _renderPass, const RenderPassDescriptor& _renderPassDesc) override final;
		void DestroyFrameBuffers(const ARenderDevice* _device) override final;

		FrameBuffer& Begin(const ARenderDevice& _device);
		void End(const ARenderDevice& _device, const std::vector<CommandBuffer>& _cmdBuffers);


		SurfaceSupportDetails QuerySupportDetails(VkPhysicalDevice _device) const;


		operator VkSurfaceKHR() const noexcept;
	};
}

#endif

#endif // GUARD
