// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/PolygonMode.hpp>

#include <Collections/Debug>

namespace Sa
{
#if SA_VULKAN

	namespace Vk
	{
		VkPolygonMode API_GetPolygonMode(PolygonMode _mode) noexcept
		{
			switch (_mode)
			{
				case Sa::PolygonMode::Point:
					return VK_POLYGON_MODE_POINT;
				case Sa::PolygonMode::Line:
					return VK_POLYGON_MODE_LINE;
				case Sa::PolygonMode::Fill:
					return VK_POLYGON_MODE_FILL;
				default:
					SA_LOG("Vulkan API GetPolygonMode [" << _mode << "L] not supported yet!", Warning, SA/Render);
					return VK_POLYGON_MODE_FILL;
			}
		}
	}

#endif
}
