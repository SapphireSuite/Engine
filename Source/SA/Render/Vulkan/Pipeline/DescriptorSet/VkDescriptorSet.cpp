// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorSet.hpp>

namespace Sa::Vk
{
	DescriptorSet::operator VkDescriptorSet() const noexcept
	{
		return mHandle;
	}
}
