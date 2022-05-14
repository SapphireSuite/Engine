// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <gtest/gtest.h>

#include <SA/Collections/Debug>

int main(int argc, char** argv)
{
//{ Init static logger instance

	SA::Logger logger;

	SA::ConsoleLogStream cslStream;
	logger.Register(cslStream);

	SA::FileLogStream fileStream;
	logger.Register(fileStream);

	// Init instance.
	SA::Debug::logger = &logger;

//}

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
