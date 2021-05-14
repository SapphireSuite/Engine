// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_FILE_STREAM_GUARD
#define SAPPHIRE_CORE_LOG_FILE_STREAM_GUARD

#include <fstream>
#include <mutex>

#include <SA/Core/Debug/Log/Streams/LogStream.hpp>

/**
*	\file FileLogStream.hpp
* 
*	\brief Log <b>file stream</b> type implementation.
* 
*	\ingroup Core_Debug
*	\{
*/


namespace Sa
{
#if SA_LOGGING

	/// Log file stream type.
	class FileLogStream : public LogStream
	{
	protected:
		/// Handled file stream.
		std::wofstream mHandle;

		/// Stream mutex.
		std::mutex mMutex;

		/// Create log and log backup files.
		void CreateLogFile(const std::string& _fileName);

	public:
		/**
		*	\e Value Constructor
		* 
		*	\param[in] _fileName	Name of file.
		*/
		SA_ENGINE_API FileLogStream(const std::string& _fileName = "log") noexcept;

		SA_ENGINE_API ~FileLogStream() noexcept;

		SA_ENGINE_API LogStream& Output(const Sa::Log& _log) override;
	};

#endif
}


/** \} */

#endif // GUARD
