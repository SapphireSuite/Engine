// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

// Test correct include path.
#include <SA/Collections/Types>

void IntTests();
void CharTests();
void InterfaceTest();

void FlagsTests();
void FunctionTests();
void EventTests();

void HasMemberTests();

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(IntTests());
	SA_UTH_GP(CharTests());
	SA_UTH_GP(InterfaceTest());


	SA_UTH_GPB(Variadics);

	SA_UTH_GP(FlagsTests());
	SA_UTH_GP(FunctionTests());
	SA_UTH_GP(EventTests());

	SA_UTH_GP(HasMemberTests());
	
	SA_UTH_GPE();


	SA_UTH_EXIT();
}
