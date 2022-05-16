// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Modes/FrontFaceMode.hpp>

#include <SA/Collections/Debug>

namespace SA
{
#if SA_VULKAN

	namespace VK
	{
		VkFrontFace API_GetFrontFaceMode(FrontFaceMode _mode) noexcept
		{
			switch (_mode)
			{
				case FrontFaceMode::Clockwise:
					return VK_FRONT_FACE_CLOCKWISE;
				case FrontFaceMode::CounterClockwise:
					return VK_FRONT_FACE_COUNTER_CLOCKWISE;
				default:
					SA_LOG("Vulkan API GetFrontFaceMode [" << _mode << "L] not supported yet!", Warning, SA/Engine/Render);
					return VK_FRONT_FACE_CLOCKWISE;
			}
		}
	}

#endif

}
