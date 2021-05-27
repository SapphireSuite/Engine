// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

// Test correct include path.
#include <SA/Collections/Maths>

void DegreeTests();
void RadianTests();

int main()
{
	SA_UTH_GP(DegreeTests());
	SA_UTH_GP(RadianTests());

	return 0;
}
