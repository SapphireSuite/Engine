// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Time/Chrono.hpp>

#include <Core/Time/Time.hpp>

namespace Sa
{
	void Chrono::Start() noexcept
	{
		mStart = Time::Ticks();
	}

	Tick Chrono::End() noexcept
	{
		return (Time::Ticks() - mStart);
	}

	Tick Chrono::Restart() noexcept
	{
		Tick temp = mStart;
		mStart = Time::Ticks();

		return (mStart - temp);
	}
}
