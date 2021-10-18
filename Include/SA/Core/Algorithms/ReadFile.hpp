// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_READ_FILE_GUARD
#define SAPPHIRE_CORE_READ_FILE_GUARD

#include <string>

namespace Sa
{
	bool ReadFile(const std::string& _path, std::string& _out);
}

#endif // GUARD
