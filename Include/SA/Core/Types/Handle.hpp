// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_HANDLE_GUARD
#define SAPPHIRE_CORE_HANDLE_GUARD

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	struct Handle
	{
		uint64 ID = uint64(-1);

		Handle() = default;
		Handle(uint64 _ID) noexcept;

		operator uint64() const noexcept;
	};
}

#endif // GUARD
