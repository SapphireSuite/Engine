// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_READ_FILE_GUARD
#define SAPPHIRE_ENGINE_READ_FILE_GUARD

#include <ios>
#include <string>

namespace Sa
{
	namespace Intl
	{
		bool ReadFile(const std::string& _path, std::string& _out, std::ios_base::openmode _mode);
	}

	bool ReadFile(const std::string& _path, std::string& _out);
	bool ReadBinaryFile(const std::string& _path, std::string& _out);
}

#endif // GUARD
