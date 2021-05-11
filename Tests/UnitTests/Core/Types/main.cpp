// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

// Test correct include path.
#include <SA/Collections/Types>

#include "IntTests.hpp"
#include "CharTests.hpp"
#include "FlagsTests.hpp"

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(IntTests());

	SA_UTH_GP(CharTests());

	SA_UTH_GP(FlagsTests());


	SA_UTH_EXIT();
}
