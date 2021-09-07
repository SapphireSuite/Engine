// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_PASS_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_PASS_GUARD

#include <SA/Render/Base/Pass/ARenderPass.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class SA_ENGINE_API RenderPass : public ARenderPass
	{
		VkRenderPass mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, const RenderPassDescriptor& _descriptor);
		void Destroy(const Device& _device);

		operator VkRenderPass() const noexcept;
	};
}

#endif

#endif // GUARD
