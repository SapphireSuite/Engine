// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Serialize/SerializeReader.hpp>

namespace Sa::Serialize
{
	Reader::Reader(std::string _str) noexcept :
		mStr{ std::move(_str) }
	{
	}


	const char* Reader::Data() const noexcept
	{
		return mStr.data() + mCursor;
	}

	void Reader::Increment(uint32 _incr) noexcept
	{
		mCursor += _incr;
	}
}
