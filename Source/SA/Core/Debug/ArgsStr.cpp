// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Debug/ArgsStr.hpp>

#include <Collections/Debug>

namespace Sa
{
	std::vector<ArgsStr::Param>* ArgsStr::operator->() noexcept
	{
		return &params;
	}
	const std::vector<ArgsStr::Param>* ArgsStr::operator->() const noexcept
	{
		return &params;
	}

	ArgsStr::Param& ArgsStr::operator[](uint32 _index)
	{
		SA_ASSERT(OutOfRange, Core, _index, 0u, params.size());

		return params[_index];
	}

	const ArgsStr::Param& ArgsStr::operator[](uint32 _index) const
	{
		SA_ASSERT(OutOfRange, Core, _index, 0u, params.size());
	
		return params[_index];
	}
}
