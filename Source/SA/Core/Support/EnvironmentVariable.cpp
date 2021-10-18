// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Support/EnvironmentVariable.hpp>

#include <Collections/Debug>

#include <cstdlib>

namespace Sa
{
	const std::string EnvironmentVariable::path = []()
	{
		std::string envPath = std::getenv("SA_ENGINE_PATH");

		SA_ASSERT(Default, SA/SDK, !envPath.empty(), L"Environment Variable [SA_ENGINE_PATH] not set! Please run the setup script in Engine folder.");

		return envPath;
	}();
}
