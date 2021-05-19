// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Core/Types/Variadics/RAII.hpp>

namespace Sa
{
	RAII<bool>::RAII(bool& _handle, bool _value) noexcept : mHandle{ _handle }
	{
		mHandle = _value;
	}

	RAII<bool>::~RAII() noexcept
	{
		mHandle = !mHandle;
	}
}
