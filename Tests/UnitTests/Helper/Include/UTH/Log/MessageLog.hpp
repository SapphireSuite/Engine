// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_MESSAGE_LOG_GUARD
#define SAPPHIRE_UTH_MESSAGE_LOG_GUARD

#include <UTH/Log/Log.hpp>

/**
*	\file MessageLog.hpp
* 
*	\brief Simple message log implementation.
* 
*	\ingroup UTH
*	\{
*/


namespace Sa::UTH
{
	/// UTH Message Log class.
	class MessageLog : public Log
	{
	public:
		/// StringToken to process on output.
		StringToken str;

		StringToken ToStringToken() const override final;
	};
}

/** \} */

#endif // GUARD
