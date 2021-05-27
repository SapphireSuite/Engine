// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

// Test correct include path.
#include <SA/Collections/Time>

void TickTests();
void MilliSecondTests();
void SecondTests();
void MinuteTests();
void HourTests();

void DateTimeTests();
void ChronoTests();


int main()
{
	SA_UTH_GP(TickTests());
	SA_UTH_GP(MilliSecondTests());
	SA_UTH_GP(SecondTests());
	SA_UTH_GP(MinuteTests());
	SA_UTH_GP(HourTests());

	SA_UTH_GP(DateTimeTests());
	SA_UTH_GP(ChronoTests());

	return 0;
}
