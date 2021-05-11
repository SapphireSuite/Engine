// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_EXCEPTION_GUARD
#define SAPPHIRE_CORE_EXCEPTION_GUARD

#include <SA/Core/Debug/Log.hpp>

namespace Sa
{
#if SA_LOGGING

	class Exception : public Log
	{
	public:
		SA_ENGINE_API Exception(
			const std::wstring& _file,
			uint32 _line,
			const std::string& _function,
			const std::wstring& _chanName,
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
