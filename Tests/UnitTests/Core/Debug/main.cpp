// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

// Test correct include path.
#include <SA/Collections/Debug>

void ToStringTests();

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(ToStringTests());


	SA_UTH_EXIT();
}
