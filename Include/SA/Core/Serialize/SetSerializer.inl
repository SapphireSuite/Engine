// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <set>

#include <SA/Core/Algorithms/SizeOf.hpp>

namespace Sa::Serialize
{
	template <typename T>
	void ToBinary(const std::set<T>& _obj, std::string& _str)
	{
		ToBinary(SizeOf<uint32>(_obj), _str);

		// Serialize one by one: can't serialize all at once (no set.data()).
		for(auto& it : _obj)
			ToBinary(it, _str);
	}

	template <typename T>
	void FromBinary(std::set<T>& _obj, Reader& _read)
	{
		uint32 size = 0u;
		FromBinary(size, _read);

		for (uint32 i = 0; i < size; ++i)
			_obj.insert(FromBinary<T>(_read));
	}
}
