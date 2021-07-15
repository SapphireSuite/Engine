// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Exceptions/Exception_Nullptr.hpp>

namespace Sa
{
#if SA_LOGGING

	Exception_Nullptr::Exception_Nullptr(
		BaseInfos&& _infos,
		bool _pred,
		std::string&& _predStr,
		std::wstring&& _details
	) noexcept :
		Exception(std::move(_infos), _pred, std::move(_predStr), Sa::ToWString(_predStr) + L" should not be nullptr!", std::move(_details))
	{
	}

#endif
}
