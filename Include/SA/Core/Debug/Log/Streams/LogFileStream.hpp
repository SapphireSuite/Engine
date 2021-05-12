// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_FILE_STREAM_GUARD
#define SAPPHIRE_CORE_LOG_FILE_STREAM_GUARD

#include <fstream>
//#include <mutex>

#include <SA/Core/Debug/Log/Streams/LogStream.hpp>

namespace Sa
{
#if SA_LOGGING

	class LogFileStream : public LogStream
	{
		std::wofstream mHandle;

		//std::mutex mMutex;

		/// Create log and log backup files.
		void CreateLogFile(const std::string& _fileName);

	public:
		/// Default constuctor.
		SA_ENGINE_API LogFileStream(const std::string& _fileName = "log") noexcept;

		SA_ENGINE_API ~LogFileStream() noexcept;

		SA_ENGINE_API LogStream& Output(const Sa::Log& _log) override final;
	};

#endif
}

#endif // GUARD
