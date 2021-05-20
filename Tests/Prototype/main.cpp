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

	std::cin.get();
	return 0;
}