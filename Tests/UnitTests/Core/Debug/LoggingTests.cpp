// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <SA/Collections/Debug>
using namespace Sa;

#if SA_LOGGING

namespace Sa::Logging_UT
{
	void Foo()
	{
		SA_LOG("Hello Foo!", Normal, FooChan);
	}
}

void LoggingTests()
{
	using namespace Sa::Logging_UT;

	const char* chw = "cstr Hello World!";
	const wchar* const cwhw = L"cwstr Hello World!";
	std::string shw = "str Hello World!";
	std::wstring wshw = L"wstr Hello World!";


	SA_LOG("Hello World!");
	SA_LOG("Hello World!", Infos);
	SA_LOG("Hello World!", Normal, TestChan / SubChan);
	SA_LOG(L"W Hello World!", Infos, TestChan / SubChan);
	SA_LOG(chw, Warning, TestChan / SubChan);
	SA_LOG(cwhw, Warning, TestChan / SubChan);
	SA_LOG(shw, Warning, TestChan / SubChan);
	SA_LOG(wshw, AssertSuccess, TestChan / SubChan);
	SA_LOG(wshw, AssertFailed, TestChan / SubChan);



	// Warnings.
	bool bWarnIfFalse = true;
	SA_WARN(bWarnIfFalse == false, TestWarn);
	SA_WARN(bWarnIfFalse == false, TestWarn, L"if Warning! pred true.");
	SA_WARN(bWarnIfFalse == true, TestWarn, L"if Warning! pred false.");


	//// Chan test.
	//LogChannel& chan = Debug::logger.GetChannel(L"FooChan");

	//Foo();

	//chan.enabled = false;

	//Foo();

	//chan.enabled = true;

	//Foo();

	//chan.levelmask.Remove(LogLevel::Normal);

	//Foo();

	//SA_LOG("Warning Hello World", Warning, TestChan/SubChan);

	//Debug::logger.globalLevelMask.Remove(LogLevel::Warning);

	//SA_LOG("Warning2 Hello World", Warning, TestChan/SubChan);

	//SA_LOG("Last Hello World", Error, TestChan/SubChan);
	//SA_LOG("Last Hello World", Infos, TestChan/SubChan);


	//int iLog = 5;
	//SA_LOG("i is: " << iLog, Infos, TestChan/SubChan);
}

#else

void LoggingTests()
{
	SA_LOG("Hello World!");
	SA_LOG("Hello World!", Infos);
	SA_LOG("Hello World!", Normal, TestChan / SubChan);
	SA_LOG(L"W Hello World!", Infos, TestChan / SubChan);

	SA_ASSERT(Default, AsChan, true, L"Test Assert Success!");
	SA_ASSERT(Default, AsChan, false, L"Test Assert Failure!");
	SA_ASSERT(OutOfRange, AsChan, 10u, 0u, 8u, L"OutOfRange failure test");

	bool bWarnIfFalse = true;
	(void)bWarnIfFalse;
	SA_WARN(bWarnIfFalse == false, TestWarn);
	SA_WARN(bWarnIfFalse == true, TestWarn, L"if Warning! pred false.");
}

#endif
