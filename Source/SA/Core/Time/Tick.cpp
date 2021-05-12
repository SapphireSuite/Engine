// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Time/Tick.hpp>

#include <Core/Time/MilliSecond.hpp>
#include <Core/Time/Second.hpp>
#include <Core/Time/Minute.hpp>
#include <Core/Time/Hour.hpp>

namespace Sa
{
	Tick::Tick(float _time) noexcept : mTime{ _time }
	{
	}

	Tick::Tick(uint64 _time) noexcept : mTime{ static_cast<float>(_time) }
	{
	}


	Tick::operator float() const noexcept
	{
		return mTime;
	}

	Tick::operator MilliSecond() const noexcept
	{
		return MilliSecond(mTime * ToMilliSeconds);
	}

	Tick::operator Second() const noexcept
	{
		return Second(mTime * ToSeconds);
	}

	Tick::operator Minute() const noexcept
	{
		return Minute(mTime * ToMinutes);
	}

	Tick::operator Hour() const noexcept
	{
		return Hour(mTime * ToHours);
	}


#if SA_LOGGING

	std::string Tick::ToString() const noexcept
	{
		return std::to_string(mTime) + "tk";
	}

#endif


	Tick operator""_tk(uint64 _lit) noexcept
	{
		return Tick(_lit);
	}

	Tick operator""_tk(long double _lit) noexcept
	{
		return Tick(static_cast<float>(_lit));
	}
}
