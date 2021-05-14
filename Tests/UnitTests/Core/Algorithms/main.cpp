// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

// Test correct include path.
#include <SA/Collections/Algorithms>

void MemCopyTests();
void MemMoveTests();

void MemFillTests();
void MemResetTests();

void BitScanForwardTests();

void SizeOfTests();

void EqualsTests();

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(MemCopyTests());
	SA_UTH_GP(MemMoveTests());

	SA_UTH_GP(MemFillTests());
	SA_UTH_GP(MemResetTests());

	SA_UTH_GP(BitScanForwardTests());

	SA_UTH_GP(SizeOfTests());

	SA_UTH_GP(EqualsTests());


	SA_UTH_EXIT();
}
