// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SUB_PASS_ATTACHMENT_LOAD_MODE_GUARD
#define SAPPHIRE_ENGINE_SUB_PASS_ATTACHMENT_LOAD_MODE_GUARD

#include <SA/Support/API/Vulkan.hpp>

namespace SA
{
	enum class AttachmentLoadMode
	{
		None,

		Load,

		Clear,
	};


#if SA_VULKAN

	namespace VK
	{
		VkAttachmentLoadOp API_GetAttachmentLoadOp(const AttachmentLoadMode _mode) noexcept;
	}

#endif
}

#endif // GUARD
