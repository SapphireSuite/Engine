// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

// Test correct include path.
#include <SA/Collections/Matrix>

void Matrix3Tests();
void Matrix4Tests();

int main()
{
	SA_UTH_GP(Matrix3Tests());
	SA_UTH_GP(Matrix4Tests());

	return 0;
}
