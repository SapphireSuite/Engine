// Copyright 2022 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_QUEUE_MGR_GUARD
#define SAPPHIRE_ENGINE_VK_QUEUE_MGR_GUARD

#include <SA/Engine/Render/Vulkan/Device/Queue/VkQueueFamilyMgr.hpp>

namespace Sa::Vk
{
	class QueueMgr
	{
	public:
		QueueFamilyMgr graphics;
		QueueFamilyMgr compute;
		QueueFamilyMgr transfer;
		QueueFamilyMgr present;
		
		const QueueFamilyMgr& GetQueueFamilyMgrFromType(QueueFamily _family) const;

		void Create(const Device& _device, const DeviceInfos& _infos);
		void Destroy(const Device& _device);
	};
}

#endif // GUARD
