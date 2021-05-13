// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/ToString.hpp>
#include <Core/Debug/Exceptions/Exception.hpp>

namespace Sa
{
#if SA_LOGGING

	Exception::Exception(
		const BaseInfos& _infos,
		bool _pred,
		const std::wstring& _msg,
		const std::wstring& _details
	) noexcept :
		Log(_infos.file, _infos.line, _infos.function, _msg, _pred ? LogLevel::AssertSuccess : LogLevel::AssertFailed, _infos.chanName, _details),
		agrsStr{ std::move(_infos.argsStr) }
	{
	}

#endif
}
