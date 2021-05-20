// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_BASE_GUARD
#define SAPPHIRE_CORE_LOG_BASE_GUARD

#include <string>

#include <SA/Core/Debug/Log/LogLevel.hpp>

namespace Sa
{
#if SA_LOGGING

	class LogBase
	{
	public:
		/// Output level.
		LogLevel level = LogLevel::Normal;

		/// Output channel name.
		std::wstring chanName = L"Default";

		/// \e Default constructor.
		LogBase() = default;

		/**
		*	\brief \e Value move constructor
		* 
		*	\param[in] _level		LogLevel of the log.
		*	\param[in] _chanName	Channel's name of the Log.
		*/
		LogBase(LogLevel _level, std::wstring&& _chanName);

		/// \e Default virtual destructor.
		virtual ~LogBase() = default;
	};

#endif
}

#endif // GUARD
