// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_MESSAGE_LOG_GUARD
#define SAPPHIRE_UTH_MESSAGE_LOG_GUARD

#include <UTH/Log/Log.hpp>

namespace Sa::UTH
{
	class MessageLog : public Log
	{
	public:
		StringToken str;

		StringToken ToStringToken() const override final;
	};
}

#endif // GUARD
