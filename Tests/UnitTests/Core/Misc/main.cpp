// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

// Test correct include path.
//#include <SA/Collections/Misc>

void RandomTests();

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(RandomTests());


	SA_UTH_EXIT();
}
