// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

// Test correct include path.
#include <SA/Collections/Maths>

void SignTests();

void CosSinTanTests();

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(SignTests());
	SA_UTH_GP(CosSinTanTests());


	SA_UTH_EXIT();
}
