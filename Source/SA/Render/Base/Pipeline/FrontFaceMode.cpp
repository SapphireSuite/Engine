// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/FrontFaceMode.hpp>

#include <Collections/Debug>

namespace Sa
{
#if SA_VULKAN

	namespace Vk
	{
		VkFrontFace API_GetFrontFaceMode(FrontFaceMode _mode) noexcept
		{
			switch (_mode)
			{
				case Sa::FrontFaceMode::Clockwise:
					return VK_FRONT_FACE_CLOCKWISE;
				case Sa::FrontFaceMode::CounterClockwise:
					return VK_FRONT_FACE_COUNTER_CLOCKWISE;
				default:
					SA_LOG("Vulkan API GetFrontFaceMode [" << _mode << "L] not supported yet!", Warning, SA/Render);
					return VK_FRONT_FACE_CLOCKWISE;
			}
		}
	}

#endif

}
