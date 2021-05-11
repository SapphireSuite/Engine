// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_CHANNEL_GUARD
#define SAPPHIRE_CORE_LOG_CHANNEL_GUARD

#include <SA/Core/Debug/LogLevel.hpp>

/**
*	\file LogChannel.hpp
*
*	\brief Log channel used by Sapphire Engine Debug class.
*
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/**
	*	\brief Sapphire Engine Debug Log channel class.
	*/
	struct LogChannel
	{
		/// Whether channel is enabled.
		bool enabled = true;

		/// Self level mask.
		Flags<LogLevel> levelmask = LogLevel::Max;
	};

#endif
}


/** \} */

#endif // GUARD
