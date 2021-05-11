// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/ToString.hpp>
#include <Core/Debug/Exceptions/Exception.hpp>

namespace Sa
{
#if SA_LOGGING

	Exception::Exception(
		const std::wstring& _file,
		uint32 _line,
		const std::string& _function,
		const std::wstring& _chanName,
		bool _pred,
		const std::wstring& _msg,
		const std::wstring& _details
	) noexcept :
		Log(_file, _line, _function, _msg, _pred ? LogLevel::AssertSuccess : LogLevel::AssertFailed, _chanName, _details)
	{
	}

#endif
}
