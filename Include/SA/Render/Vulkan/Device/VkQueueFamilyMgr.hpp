// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_FAMILY_MGR_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_FAMILY_MGR_GUARD

#include <vector>

#include <SA/Render/Vulkan/Device/VkQueue.hpp>
#include <SA/Render/Vulkan/Device/VkGraphicDeviceInfos.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class QueueFamilyMgr
	{
		std::vector<Queue> mQueues;

	public:
		Queue& GetQueue(uint32 _index);
		const Queue& GetQueue(uint32 _index) const;

		void Create(const Device& _device, const GraphicDeviceInfos::FamilyInfos& _famInfos);
		void Destroy(const Device& _device);
	};
}

#endif

#endif // GUARD
