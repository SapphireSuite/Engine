// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_FILE_STREAM_GUARD
#define SAPPHIRE_CORE_LOG_FILE_STREAM_GUARD

#include <fstream>

#include <SA/Config.hpp>

#include <SA/Core/Debug/Streams/ILogStream.hpp>

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

//{ FileLogStream

	class IFileLog;

	/// Log file stream type.
	class FileLogStream : public ILogStreamT<FileLogStream, IFileLog>
	{
	protected:
		/// Handled file stream.
		std::wofstream mHandle;

		/**
		*	\brief Create log and log backup files.
		* 
		*	\param[in] _fileName	Name of the log file.
		*/
		void CreateLogFile(const std::string& _fileName);

	public:
		/**
		*	\e Value Constructor
		* 
		*	\param[in] _fileName	Name of file.
		*/
		SA_ENGINE_API FileLogStream(const std::string& _fileName = "log") noexcept;

		SA_ENGINE_API ~FileLogStream() noexcept;

		std::wostream& operator<<(const std::wstring& _str);
	};

//}

//{ IFileLog

	class IFileLog : public ILogT<FileLogStream>
	{
	};

//}

#endif
}


/** \} */

#endif // GUARD
