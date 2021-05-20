// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UHT_RECAP_LOG_GUARD
#define SAPPHIRE_UHT_RECAP_LOG_GUARD

#include <vector>

#include <UTH/Log/TestLog.hpp>

namespace Sa::UTH
{
	class RecapLog : public Log
	{
	public:
		std::vector<TestLog> tests;

		StringToken ToStringToken() const override final;
	};
}

#endif // GUARD
