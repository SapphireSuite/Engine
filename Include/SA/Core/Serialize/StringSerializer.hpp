// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_STRING_SERIALIZER_GUARD
#define SAPPHIRE_CORE_STRING_SERIALIZER_GUARD

#include <SA/Core/Algorithms/SizeOf.hpp>
#include <SA/Core/Serialize/Serializer.hpp>

namespace Sa::Serialize
{
	void ToBinary(const std::string& _obj, std::string& _str)
	{
		ToBinary(_obj.data(), SizeOf<uint32>(_obj), _str);
	}

	void FromBinary(std::string& _str, std::string& _obj)
	{
		uint32 size = 0u;
		FromBinary(_str, size);

		_obj.resize(size);
		FromBinary(_str, _obj.data(), size);
	}
}

#endif // GUARD
