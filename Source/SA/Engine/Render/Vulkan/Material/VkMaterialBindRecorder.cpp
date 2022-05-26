// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Material/VkMaterialBindRecorder.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>

namespace SA::VK
{
	void MaterialBindRecorder::Clear()
	{
		bufferDescs.clear();
		imageDescs.clear();

		descWrites.clear();
	}

	void MaterialBindRecorder::Submit(const Device& _device)
	{
		if(descWrites.empty())
		{
			SA_LOG(L"Submit empty material bind recorder.", Warning, SA/Engine/Render/Vulkan);
			return;
		}

		vkUpdateDescriptorSets(_device, (uint32_t)descWrites.size(), descWrites.data(), 0, nullptr);

		// Auto clear after submit.
		Clear();
	}
}
