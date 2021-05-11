// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

void TickTests();
void MilliSecondTests();
void SecondTests();
void MinuteTests();
void HourTests();

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(TickTests());
	SA_UTH_GP(MilliSecondTests());
	SA_UTH_GP(SecondTests());
	SA_UTH_GP(MinuteTests());
	SA_UTH_GP(HourTests());


	SA_UTH_EXIT();
}
