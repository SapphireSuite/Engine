// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <vector>

#include <SA/Core/Algorithms/SizeOf.hpp>

namespace Sa::Serialize
{
	template <typename T>
	void ToBinary(const std::vector<T>& _obj, std::string& _str)
	{
		ToBinary(_obj.data(), SizeOf<uint32>(_obj), _str);
	}

	template <typename T>
	void FromBinary(std::vector<T>& _obj, Reader& _read)
	{
		uint32 size = 0u;
		FromBinary(size, _read);

		_obj.resize(size);
		FromBinary(_obj.data(), size, _read);
	}
}
