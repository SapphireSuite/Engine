// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_MAP_SERIALIZER_GUARD
#define SAPPHIRE_CORE_MAP_SERIALIZER_GUARD

#include <unordered_map>

#include <SA/Core/Algorithms/SizeOf.hpp>
#include <SA/Core/Serialize/PairSerializer.hpp>

namespace Sa::Serialize
{
	template <typename KeyT, typename ValueT>
	void ToBinary(const std::unordered_map<KeyT, ValueT>& _obj, std::string& _str)
	{
		ToBinary(SizeOf<uint32>(_obj), _str);

		for (auto it = _obj.cbegin(); it != _obj.cend(); ++it)
			ToBinary(*it, _str);
	}

	template <typename KeyT, typename ValueT>
	void FromBinary(std::string& _str, std::unordered_map<KeyT, ValueT>& _obj)
	{
		uint32 size = 0u;
		FromBinary(_str, size);

		_obj.reserve(size);

		for (uint32 i = 0; i < size; ++i)
		{
			std::pair<KeyT, ValueT> pair;
			FromBinary(_str, pair);

			_obj.emplace(std::move(pair));
		}
	}
}

#endif // GUARD
