// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_ILOG_GUARD
#define SAPPHIRE_CORE_ILOG_GUARD

#include <SA/Core/Debug/Log/LogBase.hpp>

/**
*	\file ILog.hpp
* 
*	\brief Log interface base implementation.
* 
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	///// Log interface base class.
	//class ILog
	//{
	//public:
	//	/// Virtual destructor (ensure correct child deletion).
	//	virtual ~ILog() = default;
	//};

	/**
	*	\brief Helper Log Interface with stream type.
	*	Define abstract Output method with stream type.
	* 
	*	\tparam StreamT	Associated stream type.
	*/
	template <typename StreamT>
	class ILogT/* : public ILog*/
	{
	public:
		/// Virtual destructor (ensure correct child deletion).
		virtual ~ILogT() = default;

		/**
		*	\brief Abstract Output from stream definition
		* 
		*	\param[in] _stream	Associated stream.
		*/
		virtual void Output(StreamT& _stream) const = 0;
	};

#endif
}


/** \} */

#endif // GUARD
