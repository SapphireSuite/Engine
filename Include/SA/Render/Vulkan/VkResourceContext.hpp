// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RESOURCE_CONTEXT_GUARD
#define SAPPHIRE_RENDER_VK_RESOURCE_CONTEXT_GUARD

#include <SA/Render/Base/ARenderResourceContext.hpp>

#include <SA/Core/Types/Variadics/ResourceHolder.hpp>

#include <SA/Render/Vulkan/Device/VkCommandPool.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class ResourceContext : public ARenderResourceContext
	{
		const Device* mDevice = nullptr;

		CommandPool mCmdPool;
	public:
		CommandBuffer cmd;
		ResourceHolder resHolder;

		void Create(const ARenderDevice* _device) override final;
		void Destroy() override final;

		void Submit() override final;
	};
}

#endif

#endif // GUARD
