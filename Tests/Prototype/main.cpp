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

	Debug::logger.levelFlags.Remove(LogLevel::Warning);

	SA_LOG("Hello 3", Warning, TestCH);
	SA_LOG("Hello 3", Infos);

	Debug::logger.Join();

	std::cin.get();
	return 0;
}