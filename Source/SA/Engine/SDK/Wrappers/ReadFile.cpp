// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/Wrappers/ReadFile.hpp>

#include <sstream>
#include <fstream>

#include <SA/Collections/Debug>

namespace SA
{
	namespace Intl
	{
		bool ReadFile(const std::string& _path, std::string& _out, std::ios_base::openmode _mode)
		{
			std::fstream fStream(_path, _mode);

			if (!fStream.is_open())
			{
				SA_LOG(L"Failed to open file {" << _path << L"}!", Error, SA/Support);
				return false;
			}


			std::stringstream sstream;
			sstream << fStream.rdbuf();

			_out = sstream.str();

			return true;
		}
	}

	bool ReadFile(const std::string& _path, std::string& _out)
	{
		return Intl::ReadFile(_path, _out, std::ios_base::in);
	}

	bool ReadBinaryFile(const std::string& _path, std::string& _out)
	{
		return Intl::ReadFile(_path, _out, std::fstream::binary | std::ios_base::in);
	}
}
