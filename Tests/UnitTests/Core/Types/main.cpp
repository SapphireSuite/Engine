// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper.hpp>

// Test correct include path.
#include <SA/Collections/Types>

void IntTests();
void CharTests();
void FlagsTests();
void HasMemberTests();

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(IntTests());
	SA_UTH_GP(CharTests());


	SA_UTH_GPB(Variadics)

	SA_UTH_GP(FlagsTests());
	SA_UTH_GP(HasMemberTests());
	
	SA_UTH_GPE()


	SA_UTH_EXIT();
}
