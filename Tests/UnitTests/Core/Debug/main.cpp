// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

// Test correct include path.
#include <SA/Collections/Debug>

void ToStringTests();
void LoggingTests();
void ExceptionTests();
void ArgsStrTests();

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(ToStringTests());
	SA_UTH_GP(ArgsStrTests());
	SA_UTH_GP(LoggingTests());
	SA_UTH_GP(ExceptionTests());


	SA_UTH_EXIT();
}
