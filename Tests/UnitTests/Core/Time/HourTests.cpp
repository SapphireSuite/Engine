// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Collections/Time>
using namespace Sa;

namespace Sa::Hour_UT
{
	void Constants()
	{
		static_assert(1.0f / Hour::ToTicks == Tick::ToHours, "1 / Hour::ToTicks != Tick::ToHours");
		static_assert(1.0f / Hour::ToMilliSeconds == MilliSecond::ToHours, "1 / Hour::ToMilliSeconds != MilliSecond::ToHours!");
		static_assert(1.0f / Hour::ToSeconds == Second::ToHours, "1 / Hour::ToSeconds != Second::ToHours!");
		static_assert(1.0f / Hour::ToMinutes == Minute::ToHours, "1 / Hour::ToMinutes != Minute::ToHours");
	}

	void Constructors()
	{
		const Hour t1 = 2.5f;
		SA_UTH_EQ(static_cast<float>(t1), 2.5f);

		const Hour t2 = 4000_ui64;
		SA_UTH_EQ(static_cast<uint64>(t2), 4000_ui64);


		const Tick tick = 3600.0f;
		const Hour t3 = tick;
		SA_UTH_EQ(static_cast<float>(t3), 0.000001f);

		const MilliSecond mil = 36.0f;
		const Hour t4 = mil;
		SA_UTH_EQ(static_cast<float>(t4), 0.00001f, std::numeric_limits<float>::epsilon());

		const Second sec = 36.0f;
		const Hour t5 = sec;
		SA_UTH_EQ(static_cast<float>(t5), 0.01f);

		const Minute min = 6.0f;
		const Hour t6 = min;
		SA_UTH_EQ(static_cast<float>(t6), 0.1f, std::numeric_limits<float>::epsilon());
	}

	void Casts()
	{
		const Hour t1 = 2.5f;
		float f = static_cast<float>(t1);
		SA_UTH_EQ(f, 2.5f);

		const Hour t2 = 4000_ui64;
		uint64 u = static_cast<uint64>(t2);
		SA_UTH_EQ(u, 4000_ui64);


		const Hour t3 = 0.000001f;
		const Tick tick = t3.operator Tick();
		SA_UTH_EQ(static_cast<float>(tick), 3600.0f);

		const Hour t4 = 0.00001f;
		const MilliSecond mil = t4.operator MilliSecond();
		SA_UTH_EQ(static_cast<float>(mil), 36.0f);

		const Hour t5 = 0.01f;
		const Second sec = t5.operator Second();
		SA_UTH_EQ(static_cast<float>(sec), 36.0f);

		const Hour t6 = 0.1f;
		const Minute min = t6.operator Minute();
		SA_UTH_EQ(static_cast<float>(min), 6.0f);
	}

	void Literal()
	{
		const Hour t1 = 2.5_hr;
		SA_UTH_EQ(static_cast<float>(t1), 2.5f);

		const Hour t2 = 4000_hr;
		SA_UTH_EQ(static_cast<uint64>(t2), 4000_ui64);
	}
}


template <>
std::string UTH::ToString(const Hour& _h)
{
	return std::to_string(static_cast<float>(_h)) + "h";
}

void HourTests()
{
	using namespace Hour_UT;

	SA_UTH_GP(Constants());
	SA_UTH_GP(Constructors());
	SA_UTH_GP(Casts());
	SA_UTH_GP(Literal());
}
