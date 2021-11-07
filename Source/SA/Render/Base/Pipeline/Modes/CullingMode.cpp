// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Modes/CullingMode.hpp>

#include <Collections/Debug>

namespace Sa
{
#if SA_VULKAN

	namespace Vk
	{
		VkCullModeFlags API_GetCullingMode(CullingMode _mode) noexcept
		{
			switch (_mode)
			{
				case Sa::CullingMode::None:
					return VK_CULL_MODE_NONE;
				case Sa::CullingMode::Front:
					return VK_CULL_MODE_FRONT_BIT;
				case Sa::CullingMode::Back:
					return VK_CULL_MODE_BACK_BIT;
				default:
					SA_LOG("Vulkan API GetCullingMode[" << _mode << L"] not supported yet!", Warning, SA/Render);
					return VK_CULL_MODE_NONE;
			}
		}
	}

#endif

}
