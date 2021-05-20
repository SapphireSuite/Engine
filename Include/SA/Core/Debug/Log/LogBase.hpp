// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_BASE_GUARD
#define SAPPHIRE_CORE_LOG_BASE_GUARD

#include <string>

#include <SA/Core/Debug/Config.hpp>

namespace Sa
{
#if SA_LOGGING

	class LogBase
	{
	public:
		virtual ~LogBase() = default;
	};

#endif
}

#endif // GUARD
