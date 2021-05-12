// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Time/Minute.hpp>

#include <Core/Time/Tick.hpp>
#include <Core/Time/MilliSecond.hpp>
#include <Core/Time/Second.hpp>
#include <Core/Time/Hour.hpp>

namespace Sa
{
	Minute::Minute(float _time) noexcept : mTime{ _time }
	{
	}

	Minute::Minute(uint64 _time) noexcept : mTime{ static_cast<float>(_time) }
	{
	}


	Minute::operator float() const noexcept
	{
		return mTime;
	}

	Minute::operator Tick() const noexcept
	{
		return Tick(mTime * ToTicks);
	}

	Minute::operator MilliSecond() const noexcept
	{
		return MilliSecond(mTime * ToMilliSeconds);
	}

	Minute::operator Second() const noexcept
	{
		return Second(mTime * ToSeconds);
	}

	Minute::operator Hour() const noexcept
	{
		return Hour(mTime * ToHours);
	}


#if SA_LOGGING

	std::string Minute::ToString() const noexcept
	{
		return std::to_string(mTime) + "min";
	}

#endif


	Minute operator""_min(uint64 _lit) noexcept
	{
		return Minute(_lit);
	}

	Minute operator""_min(long double _lit) noexcept
	{
		return Minute(static_cast<float>(_lit));
	}
}
