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

		void Begin(ARenderFrame& _frame, const Rect2Dui& _rect) override final;
		void NextSubpass(ARenderFrame& _frame) override final;
		void End(ARenderFrame& _frame) override final;

		operator VkRenderPass() const noexcept;
	};
}

#endif // GUARD
