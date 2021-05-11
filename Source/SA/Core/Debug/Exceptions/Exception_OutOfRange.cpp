// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Exceptions/Exception_OutOfRange.hpp>

namespace Sa
{
#if SA_LOGGING

	std::wstring MakeOutOfRangeMessage(uint32 _currIndex, uint32 _minBound, uint32 _maxBound)
	{
		return std::wstring(L"Index [") +
			std::to_wstring(_currIndex) + L"] is out of range [" +
			std::to_wstring(_minBound) + L',' + std::to_wstring(_maxBound) + L']';
	}

	Exception_OutOfRange::Exception_OutOfRange(
		const std::wstring& _file,
		uint32 _line,
		const std::string& _function,
		const std::wstring& _chanName,
		uint32 _currIndex,
		uint32 _minBound,
		uint32 _maxBound,
		const std::wstring& _details
	) noexcept :
		Exception(_file, _line, _function, _chanName,
			_minBound <= _currIndex && _currIndex <= _maxBound,
			MakeOutOfRangeMessage(_currIndex, _minBound, _maxBound), _details)
	{
	}

#endif
}
