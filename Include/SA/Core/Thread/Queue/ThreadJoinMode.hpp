// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_THREAD_JOIN_MODE_GUARD
#define SAPPHIRE_CORE_THREAD_JOIN_MODE_GUARD

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	enum class ThreadJoinMode : uint8
	{
		/// Complete all queued tasks on join.
		Complete = 1,

		/// Only finish current tasks and abandon queued tasks.
		Abandon,
	};
}

#endif // GUARD
