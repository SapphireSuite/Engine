// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_EXCEPTION_NULLPTR_GUARD
#define SAPPHIRE_CORE_EXCEPTION_NULLPTR_GUARD

#include <SA/Core/Debug/Exceptions/Exception.hpp>

namespace Sa
{
#if SA_LOGGING

	class Exception_Nullptr : public Exception
	{
	public:
		SA_ENGINE_API Exception_Nullptr(
			const std::wstring& _file,
			uint32 _line,
			const std::string& _function,
			const std::wstring& _chanName,
			bool _pred,
			const std::wstring& _details = L""
		) noexcept;
	};

#endif
}

#endif // GUARD
