// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Serialize/Serializer.hpp>

#include <SA/Core/Algorithms/SizeOf.hpp>

namespace Sa::Serialize
{
	namespace Intl
	{
		void ToBinary(const void* _data, uint32 _size, std::string& _str)
		{
			const uint32 prevSize = SizeOf<uint32>(_str);

			_str.resize(prevSize + _size);

			std::memcpy(_str.data() + prevSize, _data, _size);
		}

		void FromBinary(void* _data, uint32 _size, Reader& _read)
		{
			std::memcpy(_data, _read.Data(), _size);

			_read.Increment(_size);
		}
	}
}
