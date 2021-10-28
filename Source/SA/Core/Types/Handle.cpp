// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Types/Handle.hpp>

namespace Sa
{
	Handle::Handle(uint64 _ID) noexcept :
		ID{ _ID }
	{
	}


	bool Handle::IsValid() const noexcept
	{
		return ID != uint64(-1);
	}


	void Handle::Reset() noexcept
	{
		ID = uint64(-1);
	}


	Handle::operator uint64() const noexcept
	{
		return ID;
	}
}
