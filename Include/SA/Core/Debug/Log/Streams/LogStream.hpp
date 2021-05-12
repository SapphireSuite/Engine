// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_STREAM_GUARD
#define SAPPHIRE_CORE_LOG_STREAM_GUARD

#include <SA/Core/Debug/Log/Log.hpp>

namespace Sa
{
#if SA_LOGGING

	class LogStream
	{
	public:
		/**
		*	\brief Output a log.
		*
		*	\param[in] _log		Log to output.
		*
		*	\return this.
		*/
		virtual LogStream& Output(const Sa::Log& _log) = 0;

		/**
		*	\brief Output log operator.
		*
		*	\param[in] _log		Log to output.
		*
		*	\return this.
		*/
		LogStream& operator<<(const Sa::Log& _log);
	};

#endif
}

#endif // GUARD
