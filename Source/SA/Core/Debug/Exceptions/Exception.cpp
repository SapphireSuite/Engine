// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/ToString.hpp>
#include <Core/Debug/Exceptions/Exception.hpp>

namespace Sa
{
#if SA_LOGGING

	Exception::Exception(
		BaseInfos&& _infos,
		bool _pred,
		std::string&& _predStr,
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
			std::move(_details))
	{
		if (msg.empty())
			msg = Sa::ToWString(_predStr) << L" == " << _pred;
		else if(details.empty())
			details = Sa::ToWString(_predStr) << L" == " << _pred;

		agrsStr.Append(_predStr, _pred);
	}

#endif
}
