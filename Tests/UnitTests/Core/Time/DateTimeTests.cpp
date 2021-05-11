// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include <SA/Core/Time/DateTime.hpp>
using namespace Sa;

namespace DateTime_UT
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

		tm t1{ 45, 10, 2, 17, 12 - 1, 2010 - 1900, 4 };
		const DateTime d3(t1);
		SA_UTH_SF(Equals, d2, d3);
	}

	void Names()
	{
		DateTime d1;

		for (int i = 0; i < 7; ++i)
		{
			d1.weekday = i;
			SA_UTH_EQ(d1.GetDayName(), DateTime::sDays[i]);
		}

		for (int i = 1; i < 12; ++i)
		{
			d1.month = i;
			SA_UTH_EQ(d1.GetMonthName(), DateTime::sMonths[i - 1]);
		}
	}

	void Debug()
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
	SA_UTH_GP(Debug());
}
