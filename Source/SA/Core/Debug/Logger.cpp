// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>
#include <filesystem>

#include <Core/Debug/Logger.hpp>

namespace Sa
{
#if SA_LOGGING

	Logger::Logger(const std::string& _fileName) noexcept
	{
		CreateLogFile(_fileName);
	}

	Logger::~Logger() noexcept
	{
		mLogFile.close();
	}


	void Logger::CreateLogFile(const std::string& _fileName)
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

		mLogFile.open(fullName, std::ios::out);
	}

	void Logger::Output(const Sa::Log& _log) noexcept
	{
		mFileMutex.lock();

		mLogFile << _log.ToWString() << std::endl;
		std::wcout << _log.ToWString() << std::endl;

		mFileMutex.unlock();
	}

	void Logger::Log(const Sa::Log& _log) noexcept
	{
		// Level disabled.
		if (static_cast<bool>(levelFlags & _log.level) == 0)
			return;

		Output(_log);
	}

	void Logger::Assert(const Exception& _exception)
	{
		if(_exception.level == LogLevel::AssertSuccess)
			Log(_exception); // Simple log.
		else
		{
			// Force output with level in channel.
			Output(_exception);

			throw _exception;
		}
	}

#endif
}
