// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

#include "IntTests.hpp"
#include "CharTests.hpp"

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(IntTests());

	SA_UTH_GP(CharTests());


	SA_UTH_EXIT();
}