// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_ILOG_STREAM_Base_GUARD
#define SAPPHIRE_CORE_ILOG_STREAM_Base_GUARD

#include <SA/Config.hpp>

#include <SA/Core/Debug/Log/LogBase.hpp>

/**
*	\file LogStream.hpp
* 
*	\brief Log <b>base stream</b> implementation.
* 
*	Stream used by Logger.
* 
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/// Log Stream base class.
	class LogStreamBase
	{
	public:
		/**
		*	\brief Output a log.
		*
		*	\param[in] _log		Log to output.
		*
		*	\return this.
		*/
		virtual LogStreamBase& Output(const LogBase& _log) = 0;

		/**
		*	\brief Output log operator.
		*
		*	\param[in] _log		Log to output.
		*
		*	\return this.
		*/
		SA_ENGINE_API LogStreamBase& operator<<(const LogBase& _log);
	};


	template <typename StreamT, typename LogT>
	class LogStreamBaseT : public LogStreamBase
	{
	public:
		LogStreamBase& Output(const LogBase& _log) override;
	};

#endif
}


/** \} */

#include <SA/Core/Debug/Streams/LogStreamBase.inl>

#endif // GUARD
