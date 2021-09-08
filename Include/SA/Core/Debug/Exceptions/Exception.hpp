// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_EXCEPTION_GUARD
#define SAPPHIRE_CORE_EXCEPTION_GUARD

#include <SA/Core/Debug/ArgsStr.hpp>
#include <SA/Core/Debug/Log/Log.hpp>

/**
*	\file Exception.hpp
* 
*	\brief <b>Default Exception</b> type implementation.
* 
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/// Default (base) Exception type.
	class Exception : public Log
	{
	public:
		/// Base exception <b>create infos</b>.
		struct BaseInfos
		{
			/// File name.
			std::wstring file;

			/// line number.
			uint32 line;

			/// Funciton name.
			std::string function;

			/// LogChannel name.
			std::wstring chanName;
		};

		/// Generated arguments to string.
		ArgsStr agrsStr;


		/**
		*	\e Value move Constructor.
		* 
		*	\param[in] _infos		Base create infos.
		*	\param[in] _pred		Predicate used for assertion.
		*	\param[in] _predStr		Predicate as a string.
		*	\param[in] _msg			Message to display on assertion.
		*	\param[in] _details		Additional details to display on assertion.
		*/
		Exception(
			BaseInfos&& _infos,
			bool _pred,
			std::string&& _predStr,
			std::wstring&& _msg = L"",
			std::wstring&& _details = L""
		) noexcept;
	};

	/// Default type of exception.
	using Exception_Default = Exception;

	#define __SA_CREATE_EXCEPTION_Default(_baseInfos, _pred, ...) Sa::Exception_Default(\
		_baseInfos,\
		_pred,\
		#_pred,\
		##__VA_ARGS__\
	)

#endif
}


/** \} */

#endif // GUARD
