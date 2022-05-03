// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_QUEUE_FAMILY_MGR_GUARD
#define SAPPHIRE_ENGINE_VK_QUEUE_FAMILY_MGR_GUARD

#include <vector>

#include <SA/Engine/Render/Vulkan/Device/VkDeviceInfos.hpp>
#include <SA/Engine/Render/Vulkan/Device/Queue/VkQueue.hpp>

namespace Sa::Vk
{
	class QueueFamilyMgr
	{
		std::vector<Queue> mQueues;

	public:
		Queue& GetQueue(uint32_t _index);
		const Queue& GetQueue(uint32_t _index) const;


		void Create(const Device& _device, const DeviceInfos::FamilyInfos& _famInfos);
		void Destroy(const Device& _device);


		Queue& operator[](uint32_t _index);
		const Queue& operator[](uint32_t _index) const;
	};
}

#endif // GUARD
