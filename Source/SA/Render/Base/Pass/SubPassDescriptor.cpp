// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pass/SubPassDescriptor.hpp>

#include <Collections/Debug>

namespace Sa
{
#if SA_VULKAN

	namespace Vk
	{
		VkAttachmentLoadOp API_GetAttachmentLoadOp(const AttachmentLoadMode _mode) noexcept
		{
			switch (_mode)
			{
				case AttachmentLoadMode::Clear:
					return VK_ATTACHMENT_LOAD_OP_CLEAR;
				case AttachmentLoadMode::Load:
					return VK_ATTACHMENT_LOAD_OP_LOAD;
				case AttachmentLoadMode::None:
					return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				default:
					SA_LOG(L"Unknown AttachmentLoadMode [" << _mode << L"]!", Error, SA/Render);
					return VK_ATTACHMENT_LOAD_OP_CLEAR;
			}
		}
	}

#endif
}
