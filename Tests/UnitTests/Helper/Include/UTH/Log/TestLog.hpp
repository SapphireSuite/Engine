// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_TEST_LOG_GUARD
#define SAPPHIRE_UTH_TEST_LOG_GUARD

#include <UTH/Log/Log.hpp>

#include <SA/Core/Debug/ArgsStr.hpp>

/**
*	\file TestLog.hpp
* 
*	\brief UTH Log implementation for single Test.
* 
*	\ingroup UTH
*	\{
*/


namespace Sa::UTH
{
	/// UTH Test Log class.
	class TestLog : public Log
	{
	public:
		/// File name.
		std::wstring file;

		/// Line number.
		uint32 line = 0u;

		/// Function name.
		std::string function;

		/// Result value as string.
		std::string result;

		/// Group trace of Test.
		StringToken groupTrace;

		/// Test restult predicate.
		bool bResult = false;

		/// Generated arguments to string.
		ArgsStr params;


		/**
		*	\brief \e Value Constructor.
		*
		*	\param[in] _file		File of the Log.
		*	\param[in] _line		Line of the Log.
		*	\param[in] _function	Function of the Log.
		*	\param[in] _result		Test result as a string.
		*	\param[in] _bResult		Test result predicate.
		*	\param[in] _params		Test parameters.
		*/
		SA_UTH_API TestLog(
			std::wstring&& _file,
			uint32 _line,
			std::string&& _function,
			std::string&& _result,
			bool _bResult,
			ArgsStr&& _params
		) noexcept;

		SA_UTH_API StringToken ToStringToken() const  override final;
	};
}


/** \} */

#endif // GUARD
