// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/Exceptions/Exception_NonZero.hpp>

namespace Sa
{
#if SA_LOGGING

	Exception_NonZero::Exception_NonZero(
		const BaseInfos& _infos,
		bool _pred,
		const std::wstring& _details
	) noexcept :
		Exception(_infos, _pred, Sa::ToWString(_infos.argsStr[0].name) + L" should be != 0", _details)
	{
	}

#endif
}
