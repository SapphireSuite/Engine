// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

// Test correct include path.
#include <SA/Collections/Space>

void Vector2Tests();
void Vector3Tests();

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(Vector2Tests());
	SA_UTH_GP(Vector3Tests());


	SA_UTH_EXIT();
}
