// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Modes/PolygonMode.hpp>

#include <SA/Collections/Debug>

namespace SA
{
#if SA_VULKAN

	namespace VK
	{
		VkPolygonMode API_GetPolygonMode(PolygonMode _mode) noexcept
		{
			switch (_mode)
			{
				case PolygonMode::Point:
					return VK_POLYGON_MODE_POINT;
				case PolygonMode::Line:
					return VK_POLYGON_MODE_LINE;
				case PolygonMode::Fill:
					return VK_POLYGON_MODE_FILL;
				default:
					SA_LOG("Vulkan API GetPolygonMode [" << _mode << "L] not supported yet!", Warning, SA/Engine/Render);
					return VK_POLYGON_MODE_FILL;
			}
		}
	}

#endif
}
