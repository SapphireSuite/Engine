// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_QUEUE_FAMILY_GUARD
#define SAPPHIRE_ENGINE_VK_QUEUE_FAMILY_GUARD

#include <SA/Flags/Flags.hpp>

namespace SA::VK
{
	enum class QueueFamily : uint8_t
	{
		Graphics = 1 << 0,

		Compute = 1 << 1,

		Transfer = 1 << 2,

		Present = 1 << 3,

		// === Group ===
		Max = Graphics | Compute | Transfer | Present,
		OffScreen = Graphics | Compute | Transfer,
	};

	SA_DEFINE_ENUM_FLAGS(QueueFamily)
}

#endif // GUARD
