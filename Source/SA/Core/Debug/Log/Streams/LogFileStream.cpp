// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <filesystem>

#include <Core/Debug/Log/Streams/LogFileStream.hpp>

namespace Sa
{
#if SA_LOGGING

	LogFileStream::LogFileStream(const std::string& _fileName) noexcept
	{
		CreateLogFile(_fileName);
	}

	LogFileStream::~LogFileStream() noexcept
	{
		mHandle.close();
	}


	void LogFileStream::CreateLogFile(const std::string& _fileName)
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


	LogStream& LogFileStream::Output(const Sa::Log& _log)
	{
		//mMutex.lock();

		mHandle << _log.ToWString() << std::endl;

		//mMutex.unlock();

		return *this;
	}

#endif
}
