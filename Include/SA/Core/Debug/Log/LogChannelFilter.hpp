// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_CHANNEL_FILTER_GUARD
#define SAPPHIRE_CORE_LOG_CHANNEL_FILTER_GUARD

#include <unordered_map>

#include <SA/Core/Debug/Log/LogChannel.hpp>

namespace Sa
{
#if SA_LOGGING

	class LogChannelFilter
	{
	public:
		/// Registered channels.
		std::unordered_map<std::wstring, LogChannel> channels;

		bool IsChannelEnabled(const std::wstring& _chanName, LogLevel _level, uint32 _offset = 0u);
	};

#endif
}

#endif // GUARD
