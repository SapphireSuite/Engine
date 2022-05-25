// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Material/Bindings/UBOBinding.hpp>

namespace SA
{
#if SA_VULKAN

	VkDescriptorType UBOBinding::GetVkDescriptorType() const noexcept
	{
		return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	}

#endif
}
