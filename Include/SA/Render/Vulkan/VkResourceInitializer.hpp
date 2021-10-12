// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RESOURCE_INITIALIZER_GUARD
#define SAPPHIRE_RENDER_VK_RESOURCE_INITIALIZER_GUARD

#include <SA/Render/Base/ARenderResourceInitializer.hpp>

#include <SA/Core/Types/Variadics/ResourceHolder.hpp>

#include <SA/Render/Vulkan/Device/VkCommandPool.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class ResourceInitializer : public ARenderResourceInitializer
	{
		CommandPool mCmdPool;

	public:
		CommandBuffer cmd;
		ResourceHolder resHolder;

		void Create(const Device& _device);
		void Destroy(const Device& _device);

		void Submit(const Device& _device);
	};
}

#endif

#endif // GUARD
