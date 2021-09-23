// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <algorithm>

#include <Core/Debug/Debug.hpp>

#include <Core/Debug/Streams/FileLogStream.hpp>

namespace Sa::Debug
{
#if SA_LOGGING

	FileLogStream gLogFile;
	ConsoleLogStream csl;

	Logger logger;

	bool loggerInitializer = []()
	{
		logger.Register(csl);
		logger.Register(gLogFile);

		return true;
	}();

	namespace Intl
	{
		const wchar* GetFileNameFromPath(const wchar* _filePath) noexcept
		{
			// Remove characters until last backslash.
			const wchar* fileName = wcsrchr(_filePath, '\\');

			if (!fileName) // No backslash found.
				fileName = _filePath;
			else
				fileName += 1; // Remove last '\\' found.


			// Remove characters until last slash.
			if (const wchar* filePathNoSlash = wcsrchr(fileName, '/'))
			{
				// Remove last '/' found.
				fileName = filePathNoSlash + 1;
			}

			return fileName;
		}

		std::wstring RemoveSpaces(std::wstring _str) noexcept
		{
			_str.erase(std::remove_if(_str.begin(), _str.end(), isspace), _str.end());

			return _str;
		}
	}

#endif
}
