// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_RESOURCE_INITIALIZER_GUARD
#define SAPPHIRE_ENGINE_VK_RESOURCE_INITIALIZER_GUARD

#include <SA/Engine/Render/Base/Context/ARenderResourceInitializer.hpp>

#include <SA/Engine/HI/ResourceHolder.hpp>

#include <SA/Engine/Render/Vulkan/Device/Command/VkCommandPool.hpp>

namespace SA::VK
{
	class ResourceInitializer : public ARenderResourceInitializer
	{
		CommandPool mCmdPool;

		using ARenderResourceInitializer::Create; // overloaded.
		using ARenderResourceInitializer::Destroy; // overloaded.

	public:
		CommandBuffer cmd;
		ResourceHolder resHolder;

		void Create(const Device& _device);
		void Destroy(const Device& _device);

		void Submit(const Device& _device);
	};
}

#endif // GUARD
