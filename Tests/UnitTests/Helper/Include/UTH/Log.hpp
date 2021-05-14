// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_LOG_GUARD
#define SAPPHIRE_UTH_LOG_GUARD

#include <UTH/Config.hpp>

#include <SA/Collections/Debug>

namespace Sa::UTH
{
	class Log : public Sa::Log_Token
	{
		uint32 mTabNum = 0u;

	public:
		SA_UTH_API Log(
			const std::wstring& _file,
			uint32 _line,
			const std::string& _function
		) noexcept;

		void EndOfLine();
	};

	#define __SA_UTH_MAKE_LOG() Log(__SA_FILE_NAME, __LINE__, __SA_FUNC_NAME)
}

#endif // GUARD
