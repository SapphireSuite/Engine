// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_EXCEPTION_OUT_OF_RANGE_GUARD
#define SAPPHIRE_CORE_EXCEPTION_OUT_OF_RANGE_GUARD

#include <SA/Core/Debug/Exceptions/Exception.hpp>

namespace Sa
{
#if SA_LOGGING

	class Exception_OutOfRange : public Exception
	{
	public:
		uint32 currIndex = 0u;
		uint32 minBound = 0u;
		uint32 maxBound = 0u;

		SA_ENGINE_API Exception_OutOfRange(
			const std::wstring& _file,
			uint32 _line,
			const std::string& _function,
			const std::wstring& _chanName,
			uint32 _currIndex,
			uint32 _minBound,
			uint32 _maxBound,
			const std::wstring& _details = L""
		) noexcept;
	};

#endif
}

#endif // GUARD
