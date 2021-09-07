// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/Base/Pass/SampleBits.hpp>

namespace Sa
{
#if SA_VULKAN

	namespace Vk
	{
		VkSampleCountFlagBits API_GetSampleCount(SampleBits _sampleBits)
		{
			return static_cast<VkSampleCountFlagBits>(_sampleBits);
		}
	}

#endif
}
