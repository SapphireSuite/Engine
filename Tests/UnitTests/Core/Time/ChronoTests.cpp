// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Core/Time/Chrono.hpp>
#include <SA/Core/Time/Time.hpp>
#include <SA/Core/Time/MilliSecond.hpp>
using namespace Sa;

template <>
inline std::string UTH::ToString(const MilliSecond& _ms)
{
	return std::to_string(static_cast<float>(_ms)) + "ms";
}

void ChronoTests()
{
#if SA_CI
	// Handle virtual machine latency.
	const MilliSecond threshold = 200_ms;
#else
	const MilliSecond threshold = 25_ms;
#endif

	Chrono ch;

	{
		ch.Start();

		Time::Sleep(300_ms);

		const MilliSecond t1 = ch.End();
		SA_UTH_EQ(t1, 300_ms, threshold);
	}

	{
		ch.Start();

		Time::Sleep(250_ms);

		const MilliSecond t2 = ch.Restart();
		SA_UTH_EQ(t2, 250_ms, threshold);
	}

	{
		Time::Sleep(200_ms);

		const MilliSecond t3 = ch.End();
		SA_UTH_EQ(t3, 200_ms, threshold);
	}
}
