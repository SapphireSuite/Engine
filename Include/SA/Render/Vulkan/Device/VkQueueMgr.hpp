// Copyright 2021 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_MGR_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_MGR_GUARD

#include <SA/Render/Vulkan/Device/VkQueueFamilyMgr.hpp>
#include <SA/Render/Vulkan/Device/VkGraphicDeviceInfos.hpp>

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

		void Create(const Device& _device, const GraphicDeviceInfos& _infos);
		void Destroy(const Device& _device);
	};
}

#endif // GUARD
