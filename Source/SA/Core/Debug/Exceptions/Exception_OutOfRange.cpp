// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Exceptions/Exception_OutOfRange.hpp>

namespace Sa
{
#if SA_LOGGING

	Exception_OutOfRange::Exception_OutOfRange(
		BaseInfos&& _infos,
		uint32 _currIndex,
		uint32 _minBound,
		uint32 _maxBound,
		std::wstring&& _details
	) noexcept :
		Exception(std::move(_infos),
			_minBound <= _currIndex && _currIndex <= _maxBound,
			"minBound <= currIndex && currIndex <= maxBound",
			std::wstring(L"Index [") << _currIndex << L"] is out of range [" << _minBound << L',' << _maxBound << L']',
			std::move(_details)),
		currIndex{ _currIndex },
		minBound{ _minBound },
		maxBound{ _maxBound }
	{
		agrsStr.Append("currIndex, minBound, maxBound", currIndex, minBound, maxBound);
	}

#endif
}
