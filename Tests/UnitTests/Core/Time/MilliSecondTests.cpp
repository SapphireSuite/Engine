// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Collections/Time>
using namespace Sa;

namespace MilliSecond_UT
{
	void Constants()
	{
		static_assert(1.0f / MilliSecond::ToTicks == Tick::ToMilliSeconds, "1 / MilliSecond::ToTicks != Tick::ToMilliSeconds");
		static_assert(MilliSecond::ToSeconds == 1.0F / Second::ToMilliSeconds, "MilliSecond::ToSeconds != 1 / Second::ToMilliSeconds!");
		static_assert(MilliSecond::ToMinutes == 1.0F / Minute::ToMilliSeconds, "MilliSecond::ToMinutes != 1 / Minute::ToMilliSeconds!");
		static_assert(MilliSecond::ToHours == 1.0F / Hour::ToMilliSeconds, "MilliSecond::ToHours != 1 / Hour::ToMilliSeconds!");
	}

	void Constructors()
	{
		const MilliSecond t1 = 2.5f;
		SA_UTH_EQ(static_cast<float>(t1), 2.5f);

		const MilliSecond t2 = 4000_ui64;
		SA_UTH_EQ(static_cast<uint64>(t2), 4000_ui64);


		const Tick tick = 1.0f;
		const MilliSecond t3 = tick;
		SA_UTH_EQ(static_cast<float>(t3), 0.001f);

		const Second sec = 1.0f;
		const MilliSecond t4 = sec;
		SA_UTH_EQ(static_cast<float>(t4), 1000.0f);

		const Minute min = 1.0f;
		const MilliSecond t5 = min;
		SA_UTH_EQ(static_cast<float>(t5), 60000.0f);

		const Hour hour = 1.0f;
		const MilliSecond t6 = hour;
		SA_UTH_EQ(static_cast<float>(t6), 3600000.0f);
	}

	void Casts()
	{
		const MilliSecond t1 = 2.5f;
		float f = static_cast<float>(t1);
		SA_UTH_EQ(f, 2.5f);

		const MilliSecond t2 = 4000_ui64;
		uint64 u = static_cast<uint64>(t2);
		SA_UTH_EQ(u, 4000_ui64);


		const MilliSecond t3 = 0.001f;
		const Tick tick = t3.operator Tick();
		SA_UTH_EQ(static_cast<float>(tick), 1.0f);

		const MilliSecond t4 = 1000.0f;
		const Second sec = t4.operator Second();
		SA_UTH_EQ(static_cast<float>(sec), 1.0f);

		const MilliSecond t5 = 60000.0f;
		const Minute min = t5.operator Minute();
		SA_UTH_EQ(static_cast<float>(min), 1.0f);

		const MilliSecond t6 = 3600000.0f;
		const Hour hour = t6.operator Hour();
		SA_UTH_EQ(static_cast<float>(hour), 1.0f);
	}

	void Literal()
	{
		const MilliSecond t1 = 2.5_ms;
		SA_UTH_EQ(static_cast<float>(t1), 2.5f);

		const MilliSecond t2 = 4000_ms;
		SA_UTH_EQ(static_cast<uint64>(t2), 4000_ui64);
	}
}


template <>
inline std::string UTH::ToString(const MilliSecond& _ms)
{
	return std::to_string(static_cast<float>(_ms)) + "ms";
}

void MilliSecondTests()
{
	using namespace MilliSecond_UT;

	SA_UTH_GP(Constants());
	SA_UTH_GP(Constructors());
	SA_UTH_GP(Casts());
	SA_UTH_GP(Literal());
}
