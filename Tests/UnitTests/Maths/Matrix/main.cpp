// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

// Test correct include path.
//#include <SA/Collections/Algorithms>

void Matrix3Tests();

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(Matrix3Tests());


	SA_UTH_EXIT();
}
