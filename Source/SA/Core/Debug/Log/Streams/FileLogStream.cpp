// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <filesystem>

#include <Core/Debug/Log/Streams/FileLogStream.hpp>

// ToDo: Wait for github action fix std::filesystem linkage.
#include <Core/Support/Compilers.hpp>
#define __SA_NO_FILESTREAM (SA_CI && SA_CLANG && __clang_major__ == 9)

namespace Sa
{
#if SA_LOGGING

	FileLogStream::FileLogStream(const std::string& _fileName) noexcept
	{
#if !__SA_NO_FILESTREAM

		CreateLogFile(_fileName);

#endif
	}

	FileLogStream::~FileLogStream() noexcept
	{
#if !__SA_NO_FILESTREAM

		mHandle.close();

#endif
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


	LogStream& FileLogStream::Output(const Sa::Log& _log)
	{
#if !__SA_NO_FILESTREAM

		mHandle << _log.ToWString() << std::endl;

#endif

		return *this;
	}

#endif
}
