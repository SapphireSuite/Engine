// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPIRE_ENGINE_VK_RENDER_PASS_GUARD
#define SAPPIRE_ENGINE_VK_RENDER_PASS_GUARD

#include <SA/Engine/Render/Base/Pass/ARenderPass.hpp>

#include <SA/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	class Device;

	class RenderPass : public ARenderPass
	{
		VkRenderPass mHandle = VK_NULL_HANDLE;

		using ARenderPass::Create; 	// overloaded.
		using ARenderPass::Destroy;	// overloaded.

	public:
		void Create(const Device& _device, const RenderPassDescriptor& _desc);
		void Destroy(const Device& _device);

		operator VkRenderPass() const noexcept;
	};
}

#endif // GUARD
