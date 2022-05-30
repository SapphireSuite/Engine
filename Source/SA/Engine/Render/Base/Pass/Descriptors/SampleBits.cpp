// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SA/Engine/Render/Base/Pass/Descriptors/SampleBits.hpp>

namespace SA
{
#if SA_VULKAN

	namespace VK
	{
		VkSampleCountFlagBits API_GetSampleCount(SampleBits _sampleBits)
		{
			return static_cast<VkSampleCountFlagBits>(_sampleBits);
		}
	}

#endif
}
