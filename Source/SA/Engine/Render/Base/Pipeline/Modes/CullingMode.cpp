// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Modes/CullingMode.hpp>

#include <SA/Collections/Debug>

namespace SA
{
#if SA_VULKAN

	namespace VK
	{
		VkCullModeFlags API_GetCullingMode(CullingMode _mode) noexcept
		{
			switch (_mode)
			{
				case CullingMode::None:
					return VK_CULL_MODE_NONE;
				case CullingMode::Front:
					return VK_CULL_MODE_FRONT_BIT;
				case CullingMode::Back:
					return VK_CULL_MODE_BACK_BIT;
				default:
					SA_LOG("Vulkan API GetCullingMode[" << _mode << L"] not supported yet!", Warning, SA/Engine/Render);
					return VK_CULL_MODE_NONE;
			}
		}
	}

#endif

}
