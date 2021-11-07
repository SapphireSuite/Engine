// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD
#define SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	class DescriptorSet
	{
		VkDescriptorSet mHandle = VK_NULL_HANDLE;

		friend class DescriptorPool;

	public:
		operator VkDescriptorSet() const noexcept;
	};
}

#endif // GUARD
