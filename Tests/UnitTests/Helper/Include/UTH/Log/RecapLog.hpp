// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UHT_RECAP_LOG_GUARD
#define SAPPHIRE_UHT_RECAP_LOG_GUARD

#include <vector>

#include <UTH/Log/TestLog.hpp>

/**
*	\file RecapLog.hpp
* 
*	\brief Group of TestLog used as recap.
* 
*	\ingroup UTH
*	\{
*/


namespace Sa::UTH
{
	/// Recap log class.
	class RecapLog : public Log
	{
	public:
		/// Saved TestLog for recap.
		std::vector<TestLog> tests;

		StringToken ToStringToken() const override final;
	};
}


/** \} */

#endif // GUARD
