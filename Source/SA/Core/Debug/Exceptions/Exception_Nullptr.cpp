// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Exceptions/Exception_Nullptr.hpp>

namespace Sa
{
#if SA_LOGGING

	Exception_Nullptr::Exception_Nullptr(
		const std::wstring& _file,
		uint32 _line,
		const std::string& _function,
		const std::wstring& _chanName,
		const void* _ptr,
		const std::wstring& _details
	) noexcept :
		Exception(_file, _line, _function, _chanName, _ptr, L"<var> is nullptr!", _details)
	{
	}

#endif
}
