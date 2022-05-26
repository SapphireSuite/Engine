// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_MATERIAL_BIND_RECORDER_GUARD
#define SAPPHIRE_ENGINE_VK_MATERIAL_BIND_RECORDER_GUARD

#include <list>
#include <vector>

#include <SA/Support/API/Vulkan.hpp>

namespace SA::VK
{
	class Device;

	struct MaterialBindRecorder
	{
	public:
		std::list<std::vector<VkDescriptorBufferInfo>> bufferDescs;
		std::list<std::vector<VkDescriptorImageInfo>> imageDescs;

		std::vector<VkWriteDescriptorSet> descWrites;

		void Clear();

		void Submit(const Device& _device);
	};
}

#endif // GUARD
