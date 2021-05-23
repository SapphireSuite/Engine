// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Exceptions/Exception_NonZero.hpp>

namespace Sa
{
#if SA_LOGGING

	Exception_NonZero::Exception_NonZero(
		BaseInfos&& _infos,
		bool _pred,
		std::wstring&& _details
	) noexcept :
		Exception(std::move(_infos), _pred, Sa::ToWString(_infos.argsStr[0].name) + L" should be != 0", std::move(_details))
	{
	}

#endif
}
