// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_ILOG_STREAM_GUARD
#define SAPPHIRE_CORE_ILOG_STREAM_GUARD

#include <SA/Core/Debug/Log/ILog.hpp>

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
	class ILogStream
	{
	public:
		/**
		*	\brief Output a log.
		*
		*	\param[in] _log		Log to output.
		*
		*	\return this.
		*/
		virtual ILogStream& Output(const ILog& _log) = 0;

		/**
		*	\brief Output log operator.
		*
		*	\param[in] _log		Log to output.
		*
		*	\return this.
		*/
		ILogStream& operator<<(const ILog& _log);
	};


	template <typename StreamT, typename LogT>
	class ILogStreamT : public ILogStream
	{
	public:
		ILogStream& Output(const ILog& _log) override;
	};

#endif
}


/** \} */

#include <SA/Core/Debug/Streams/ILogStream.inl>

#endif // GUARD
