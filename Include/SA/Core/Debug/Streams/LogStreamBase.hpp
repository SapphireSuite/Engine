// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_ILOG_STREAM_Base_GUARD
#define SAPPHIRE_CORE_ILOG_STREAM_Base_GUARD

#include <SA/Config.hpp>

#include <SA/Core/Debug/Log/LogBase.hpp>

/**
*	\file LogStreamBase.hpp
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
		LogStreamBase& operator<<(const LogBase& _log);
	};


	/**
	*	\brief Helper LogStream type class.
	*	Define default Output method using LogT interface.
	*
	*	\tparam StreamT		Child stream type.
	*	\tparam LogT		Associated log interface type.
	*/
	template <typename StreamT, typename LogT>
	class LogStreamBaseT : public LogStreamBase
	{
	public:
		/**
		*	\brief Default output implementation.
		*	Cast LogBase into LogT interface and call Output with this as StreamT.
		* 
		*	\param[in] _log		Log to process.
		* 
		*	\return this.
		*/
		LogStreamBase& Output(const LogBase& _log) override;
	};

#endif
}


/** \} */

#include <SA/Core/Debug/Streams/LogStreamBase.inl>

#endif // GUARD
