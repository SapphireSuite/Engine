// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_ENVIRONMENT_VARIABLE_GUARD
#define SAPPHIRE_CORE_ENVIRONMENT_VARIABLE_GUARD

#include <string>

namespace Sa
{
	class EnvironmentVariable
	{
	public:
		static const std::string path;
	};

	using EnvVar = EnvironmentVariable;
}

#endif // GUARD
