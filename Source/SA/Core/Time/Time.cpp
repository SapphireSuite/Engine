// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <ctime>

#include <Core/Time/Time.hpp>

#include <Core/Time/MilliSecond.hpp>

#include <Collections/Debug>

#if SA_WIN

	#include <Core/Support/API/Windows.hpp>

#else

	#include <unistd.h>

#endif

namespace Sa
{
#if SA_WIN

	/// Queried time at the beginnig of the program (in hardware counts).
	const uint64 gStartTime = []()
	{
		LARGE_INTEGER start;

		SA_ASSERT_EXEC(Default, Core, QueryPerformanceCounter(&start), L"High resolution time stamp not supported!");

		return static_cast<uint64>(start.QuadPart);
	}();

	/// Hardware dependant constant to convert <b> hardware ticks </b> to <b> Sappire Engine Tick </b> (multiplication).
	const float gHardwareFrequency = []()
	{
		LARGE_INTEGER frequency;

		SA_ASSERT_EXEC(Default, Core, QueryPerformanceFrequency(&frequency), L"High resolution time stamp not supported!");

		return Second::ToTicks / static_cast<float>(frequency.QuadPart);
	}();

#else

	/// Queried time at the beginnig of the program.
	const Tick gStartTime = Time::Ticks();

#endif

	Second Time::Now()
	{
		return Ticks(); // Auto convertion.
	}

	Tick Time::Ticks()
	{
#if SA_WIN

		LARGE_INTEGER end;

		SA_ASSERT_EXEC(Default, Core, QueryPerformanceCounter(&end), L"High resolution time stamp not supported!");

		return (end.QuadPart - gStartTime) * gHardwareFrequency;

#else

		struct timespec end;

		SA_ASSERT_EXEC(Default, Core, clock_gettime(CLOCK_MONOTONIC, &end) == 0, L"High resolution time stamp not supported!");


		return (end.tv_sec * Second::ToTicks + end.tv_nsec / 1000.0f) - gStartTime;

#endif
	}

	DateTime Time::Date() noexcept
	{
		tm qTime; // Queried time.
		const time_t currTime = time(nullptr);

#if SA_WIN
		localtime_s(&qTime, &currTime);
#else
		localtime_r(&currTime, &qTime);
#endif

		return DateTime{ qTime };
	}
	
	DateTime Time::GMDate() noexcept
	{
		tm qTime; // Queried time.
		const time_t currTime = time(nullptr);

#if SA_WIN
		gmtime_s(&qTime, &currTime);
#else
		gmtime_r(&currTime, &qTime);
#endif

		return DateTime{ qTime };
	}

	uint64 Time::Seed() noexcept
	{
		return time(nullptr);
	}

	void Time::Sleep(MilliSecond _ms) noexcept
	{
#if SA_WIN
		::Sleep(static_cast<uint32>(_ms));
#else
		usleep(Tick(_ms));
#endif
	}
}
