// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_LOG_FILE_STREAM_GUARD
#define SAPPHIRE_CORE_LOG_FILE_STREAM_GUARD

#include <fstream>

#include <SA/Core/Debug/Log/ILog.hpp>
#include <SA/Core/Debug/Streams/LogStreamBase.hpp>

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
	class FileLogStream : public LogStreamBaseT<FileLogStream, IFileLog>
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
		FileLogStream(const std::string& _fileName = "log") noexcept;

		/**
		*	\e Destructor. Close the file stream.
		*/
		~FileLogStream() noexcept;

		/**
		*	\brief Output wstring into the stream.
		* 
		*	\param[in] _str		String to output.
		* 
		*	\return handled std::wostream.
		*/
		std::wostream& operator<<(const std::wstring& _str);
	};

//}

//{ IFileLog

	/// File Log interface implementation.
	class IFileLog : public ILogT<FileLogStream>
	{
	};

//}

#endif
}


/** \} */

#endif // GUARD
