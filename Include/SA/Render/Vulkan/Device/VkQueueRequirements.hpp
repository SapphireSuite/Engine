// Copyright 2021 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_REQUIREMENTS_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_REQUIREMENTS_GUARD

#include <SA/Render/Vulkan/Device/VkQueueFamily.hpp>

namespace Sa::Vk
{
	struct QueueRequirements
	{
		QueueFamily familyFlags = QueueFamily::Max;

		uint32 graphicNum = 1;
		uint32 computeNum = 1;
		uint32 transferNum = 1;
		uint32 presentNum = 1;
	};
}

#endif // GUARD
