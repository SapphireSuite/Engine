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
			const std::wstring& file;

			/// line number.
			uint32 line;

			/// Funciton name.
			const std::string& function;

			/// LogChannel name.
			const std::wstring& chanName;

			/// Generated ArgsStr from macro parameters.
			ArgsStr argsStr;
		};

		/// Generated arguments to string.
		ArgsStr agrsStr;

		/**
		*	\e Value Constructor.
		* 
		*	\param[in] _infos		Base create infos.
		*	\param[in] _pred		Predicate used for assertion.
		*	\param[in] _msg			Message to display on assertion.
		*	\param[in] _details		Additional details to display on assertion.
		*/
		SA_ENGINE_API Exception(
			const BaseInfos& _infos,
			bool _pred,
			const std::wstring& _msg,
			const std::wstring& _details = L""
		) noexcept;
	};

	/// Default type of exception.
	using Exception_Default = Exception;

#endif
}


/** \} */

#endif // GUARD
