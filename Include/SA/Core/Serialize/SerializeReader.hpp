// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_SERIALIZE_READER_GUARD
#define SAPPHIRE_CORE_SERIALIZE_READER_GUARD

#include <string>

#include <SA/Core/Types/Int.hpp>

namespace Sa::Serialize
{
	class Reader
	{
		uint32 mCursor = 0u;
		std::string mStr;

	public:
		Reader(std::string _str) noexcept;

		const char* Data() const noexcept;
		void Increment(uint32 _incr) noexcept;
	};
}

#endif // GUARD
