// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Algorithms/ReadFile.hpp>

#include <sstream>
#include <fstream>

#include <Core/Debug.hpp>

namespace Sa
{
	bool ReadFile(const std::string& _path, std::string& _out)
	{
		std::fstream fStream(_path, std::ios_base::in);

		if (!fStream.is_open())
		{
			SA_LOG(L"Failed to open file {" << _path << L"}!", Error, SA/Core);
			return false;
		}


		std::stringstream sstream;
		sstream << fStream.rdbuf();

		_out = sstream.str();

		return true;
	}
}
