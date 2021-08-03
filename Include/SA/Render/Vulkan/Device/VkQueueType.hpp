// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_TYPE_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_TYPE_GUARD

#include <SA/Core/Types/Variadics/Flags.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	enum class QueueType : uint8
	{
		Graphics = 1 << 0,

		Compute = 1 << 1,

		Transfer = 1 << 2,

		Present = 1 << 3,

		// === Group ===
		Max = Graphics | Compute | Transfer | Present,
	};

	SA_DEFINE_ENUM_FLAGS(QueueType)
}

#endif

#endif // GUARD
