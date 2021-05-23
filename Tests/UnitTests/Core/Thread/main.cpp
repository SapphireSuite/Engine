// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UnitTestHelper>

// Test correct include path.
#include <SA/Collections/Thread>

void TheadPipelineEngineTests();
void TheadPipelineLoopTests();

int main()
{
	SA_UTH_INIT();


	SA_UTH_GP(TheadPipelineEngineTests());
	SA_UTH_GP(TheadPipelineLoopTests());


	SA_UTH_EXIT();
}
