// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_DESCRIPTOR_SET_UPDATER_GUARD
#define SAPPHIRE_ENGINE_VK_DESCRIPTOR_SET_UPDATER_GUARD

#include <list>
#include <vector>

#include <SA/Engine/Render/Vulkan/Material/VkDescriptorSet.hpp>

namespace SA::VK
{
	struct DescriptorSetUpdater
	{
		const std::vector<DescriptorSet>& sets;

		std::list<std::vector<VkDescriptorBufferInfo>> bufferDescs;
		std::list<std::vector<VkDescriptorImageInfo>> imageDescs;

		inline DescriptorSetUpdater(const std::vector<DescriptorSet>& _sets) noexcept :
			sets{ _sets }
		{
		}
	};
}

#endif // GUARD
