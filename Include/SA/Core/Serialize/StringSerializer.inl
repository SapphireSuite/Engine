// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Core/Algorithms/SizeOf.hpp>

namespace Sa::Serialize
{
	inline void ToBinary(const std::string& _obj, std::string& _str)
	{
		ToBinary(_obj.data(), SizeOf<uint32>(_obj), _str);
	}

	inline void FromBinary(std::string& _obj, Reader& _read)
	{
		uint32 size = 0u;
		FromBinary(size, _read);

		_obj.resize(size);
		FromBinary(_obj.data(), size, _read);
	}
}
