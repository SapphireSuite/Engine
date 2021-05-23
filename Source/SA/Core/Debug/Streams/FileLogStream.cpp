// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <filesystem>

#include <Core/Debug/Streams/FileLogStream.hpp>

#include <Core/Time/DateTime.hpp>

namespace Sa
{
#if SA_LOGGING

//{ FileLogStream

	FileLogStream::FileLogStream(const std::string& _fileName) noexcept
	{
		CreateLogFile(_fileName);
	}

	FileLogStream::~FileLogStream() noexcept
	{
		mHandle.close();
	}


	void FileLogStream::CreateLogFile(const std::string& _fileName)
	{
		std::filesystem::create_directories("Logs");

		std::string fullName = "Logs/" + _fileName + ".txt";

		// Log file already exists? Create backup.
		if (std::filesystem::exists(fullName))
		{
			// Query old file time infos.
			DateTime backupStat = DateTime::FileStats(fullName);

			std::rename(fullName.c_str(), ("Logs/" + _fileName + "_backup-" + backupStat.ToString() + ".txt").c_str());
		}

		mHandle.open(fullName, std::ios::out);
	}


	std::wostream& FileLogStream::operator<<(const std::wstring& _str)
	{
		return mHandle << _str;
	}

//}

#endif
}
