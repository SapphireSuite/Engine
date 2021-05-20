// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#define LOG(_str) std::cout << _str << std::endl;

#include <SA/Collections/Debug>
using namespace Sa;

int main()
{
	SA_LOG("Hello 1");
	SA_LOG("Hello 2", Infos);
	SA_LOG("Hello 2", Warning, TestCH);
	
	Debug::logger.Join();

	SA_LOGLVL_DIS_SECTB(Warning)

		SA_LOG("Hello 3", Warning, TestCH);
		SA_LOG("Hello 3", Infos);

	SA_LOGLVL_DIS_SECTE()

	SA_LOG("Hello 4", Warning, TestCH);

	Debug::logger.Join();

	LogChannel& fooChan = Debug::logger.GetChannel(L"FooChan");

	fooChan.Disable();

	SA_LOG("Foo 1", Infos, FooChan);
	Debug::logger.Join();

	fooChan.Enable();
	
	SA_LOG("Foo 2", Infos, FooChan);

	Debug::logger.Join();

	{
		const uint32 min = 0u;
		const uint32 max = 8u;
		const uint32 goodI = 4u;
		const uint32 wrongI = 10u;

		SA_ASSERT(OutOfRange, AsChan, goodI, min, max, L"OutOfRange success test");

		try
		{
			SA_ASSERT(Default, AsChan, true, L"OutOfRange failure test");
			SA_ASSERT(OutOfRange, AsChan, wrongI, min, max, L"OutOfRange failure test");
		}
		catch (const Exception_OutOfRange& _e)
		{
			std::wcout << L"Exception caugth: " << _e.msg << '\n' << _e.details << '\n' << std::endl;
		}
	}



	std::cin.get();
	return 0;
}