// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_TEST_LOG_GUARD
#define SAPPHIRE_UTH_TEST_LOG_GUARD

#include <UTH/Log/Log.hpp>

#include <SA/Core/Debug/ArgsStr.hpp>

namespace Sa::UTH
{
	class TestLog : public Log
	{
	public:
		std::wstring file;

		uint32 line = 0u;

		std::string function;

		std::string result;

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

#endif // GUARD
