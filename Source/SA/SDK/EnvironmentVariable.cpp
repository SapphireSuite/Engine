// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/EnvironmentVariable.hpp>

#include <Collections/Debug>

#include <cstdlib>

namespace Sa
{
	const std::string EnvironmentVariable::path = []()
	{
		//uint64 size = 0u;
		//char buffer[255]{}; // Max path length.

		std::string envPath = std::getenv("SA_ENGINE_PATH");

		SA_ASSERT(Default, SA/SDK, !envPath.empty(), L"Environment Variable [SA_ENGINE_PATH] not set! Please run the setup script in Engine folder.");

		return envPath;

		//SA_ASSERT_EXEC(Default, SA/SDK, getenv_s(&size, &buffer, "SA_ENGINE_PATH") == 0, L"Environment Variable [SA_ENGINE_PATH] not set! Please run the setup script in Engine folder.");

		//return std::string{ buffer, buffer + size };
	}();
}
