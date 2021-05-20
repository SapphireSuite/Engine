// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_CHANNEL_GUARD
#define SAPPHIRE_CORE_LOG_CHANNEL_GUARD

#include <atomic>

#include <SA/Core/Debug/Log/LogLevel.hpp>

/**
*	\file LogChannel.hpp
*
*	\brief <b>Log channel</b> type implementation.
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
		/// Self level mask.
		Flags<LogLevel, std::atomic<UIntOfSize<sizeof(LogLevel)>>> levelFlags = LogLevel::Default;

		/// Enable this channel (if not already).
		inline void Enable()
		{
			if(levelFlags)
				levelFlags = LogLevel::Default;
		}

		/// Disable this channel.
		inline void Disable()
		{
			levelFlags = 0u;
		}

		/**
		*	\brief Set this channel enabled.
		* 
		*	\param[in] _bEnable		Wether to enable.
		*/
		inline void SetEnabled(bool _bEnable)
		{
			if (_bEnable)
				Enable();
			else
				Disable();
		}
	};

#endif
}


/** \} */

#endif // GUARD
