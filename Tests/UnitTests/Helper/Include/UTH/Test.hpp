// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_TEST_GUARD
#define SAPPHIRE_UTH_TEST_GUARD

#include <UTH/Config.hpp>

#include <SA/Core/Debug/ArgsStr.hpp>
#include <SA/Core/Debug/Log/Log_Token.hpp>

namespace Sa::UTH
{
	class Test
	{
	public:
		const std::wstring& file;
		
		uint32 line = 0u;

		const std::string& function;

		const std::string& result;

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
		SA_UTH_API Test(
			const std::wstring& _file,
			uint32 _line,
			const std::string& _function,
			const std::string& _result,
			bool _bResult,
			ArgsStr&& _params
		) noexcept;

		Log_Token MakeLog() const;
	};
}

#endif // GUARD
