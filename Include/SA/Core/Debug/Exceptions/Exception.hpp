// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_EXCEPTION_GUARD
#define SAPPHIRE_CORE_EXCEPTION_GUARD

#include <SA/Core/Debug/ArgsStr.hpp>
#include <SA/Core/Debug/Log/Log.hpp>

namespace Sa
{
#if SA_LOGGING

	class Exception : public Log
	{
	public:
		struct BaseInfos
		{
			const std::wstring& file;
			uint32 line;
			const std::string& function;
			const std::wstring& chanName;
			ArgsStr argsStr;
		};

		/// Generated arguments to string.
		ArgsStr agrsStr;

		SA_ENGINE_API Exception(
			const BaseInfos& _infos,
			bool _pred,
			const std::wstring& _msg,
			const std::wstring& _details = L""
		) noexcept;
	};

	/// Default type of exception.
	using Exception_Default = Exception;

#endif
}

#endif // GUARD
