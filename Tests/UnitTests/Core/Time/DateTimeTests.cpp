// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <cstring>

#include <UnitTestHelper>

#include <SA/Core/Time/DateTime.hpp>
using namespace Sa;

namespace Sa::DateTime_UT
{
	bool Equals(const DateTime& _rhs, const DateTime& _lhs)
	{
		return _rhs.second == _lhs.second &&
			_rhs.minute == _lhs.minute &&
			_rhs.hour == _lhs.hour &&
			_rhs.day == _lhs.day &&
			_rhs.month == _lhs.month &&
			_rhs.year == _lhs.year &&
			_rhs.weekday == _lhs.weekday;
	}

	void Constructors()
	{
		const DateTime d1;
		SA_UTH_EQ(d1.second, 0_ui8);
		SA_UTH_EQ(d1.minute, 0_ui8);
		SA_UTH_EQ(d1.hour, 0_ui8);
		SA_UTH_EQ(d1.day, 0_ui8);
		SA_UTH_EQ(d1.month, 0_ui8);
		SA_UTH_EQ(d1.year, 0_ui16);
		SA_UTH_EQ(d1.weekday, 0_ui8);

		const DateTime d2{ 45_ui8, 10_ui8, 2_ui8, 17_ui8, 12_ui8, 2010_ui16, 4_ui8 };
		SA_UTH_EQ(d2.second, 45_ui8);
		SA_UTH_EQ(d2.minute, 10_ui8);
		SA_UTH_EQ(d2.hour, 2_ui8);
		SA_UTH_EQ(d2.day, 17_ui8);
		SA_UTH_EQ(d2.month, 12_ui8);
		SA_UTH_EQ(d2.year, 2010_ui16);
		SA_UTH_EQ(d2.weekday, 4_ui8);

		tm t1{};
		t1.tm_sec = 45;
		t1.tm_min = 10;
		t1.tm_hour = 2;
		t1.tm_mday = 17;
		t1.tm_mon = 12 - 1;
		t1.tm_year = 2010 - 1900;
		t1.tm_wday = 4;
		const DateTime d3(t1);
		SA_UTH_SF(Equals, d2, d3);
	}

	void Names()
	{
		DateTime d1;

		for (uint8 i = 0_ui8; i < 7_ui8; ++i)
		{
			d1.weekday = i;
			SA_UTH_RSF(0, strcmp, d1.GetDayName(), DateTime::sDays[i]);
		}

		for (uint8 i = 1_ui8; i < 12_ui8; ++i)
		{
			d1.month = i;
			SA_UTH_RSF(0, strcmp, d1.GetMonthName(), DateTime::sMonths[i - 1]);
		}
	}

	void String()
	{
#if SA_LOGGING

		const DateTime d1{ 45_ui8, 10_ui8, 2_ui8, 17_ui8, 12_ui8, 2010_ui16, 4_ui8 };
		SA_UTH_EQ(d1.ToString(), std::string("12.17.2010-2h10m45s"));

#endif
	}
}

void DateTimeTests()
{
	using namespace DateTime_UT;

	SA_UTH_GP(Constructors());
	SA_UTH_GP(Names());
	SA_UTH_GP(String());
}
