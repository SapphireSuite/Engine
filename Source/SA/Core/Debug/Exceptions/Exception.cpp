// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/ToString.hpp>
#include <Core/Debug/Exceptions/Exception.hpp>

namespace Sa
{
#if SA_LOGGING

	Exception::Exception(
		BaseInfos&& _infos,
		bool _pred,
		std::wstring&& _msg,
		std::wstring&& _details
	) noexcept :
		Log(
			std::move(_infos.file),
			_infos.line,
			std::move(_infos.function),
			std::move(_msg),
			_pred ? LogLevel::AssertSuccess : LogLevel::AssertFailed,
			std::move(_infos.chanName),
			std::move(_details)),
		agrsStr{ std::move(_infos.argsStr) }
	{
	}

#endif
}
