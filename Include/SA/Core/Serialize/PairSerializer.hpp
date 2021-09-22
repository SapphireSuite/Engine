// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_PAIR_SERIALIZER_GUARD
#define SAPPHIRE_CORE_PAIR_SERIALIZER_GUARD

#include <utility>

#include <SA/Core/Serialize/Serializer.hpp>

namespace Sa::Serialize
{
	template <typename T1, typename T2>
	void ToBinary(const std::pair<T1, T2>& _obj, std::string& _str)
	{
		ToBinary(_obj.first, _str);
		ToBinary(_obj.second, _str);
	}

	template <typename T1, typename T2>
	void FromBinary(std::string& _str, std::pair<T1, T2>& _obj)
	{
		FromBinary(_str, _obj.first);
		FromBinary(_str, _obj.second);
	}
}

#endif // GUARD
