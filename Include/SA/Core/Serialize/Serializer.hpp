// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_SERIALIZER_GUARD
#define SAPPHIRE_CORE_SERIALIZER_GUARD

#include <SA/Core/Serialize/SerializeReader.hpp>

namespace Sa::Serialize
{
	namespace Intl
	{
		void ToBinary(const void* _data, uint32 _size, std::string& _str);
		void FromBinary(void* _data, uint32 _size, Reader& _read);
	}
		

	template <typename T>
	struct Specs
	{
		static constexpr bool bContinuousData = std::is_arithmetic<T>::value;
	};


//{ To Binary

	template <typename T>
	std::string ToBinary(const T& _obj);

	template <typename T>
	void ToBinary(const T& _obj, std::string& _str);

	template <typename T>
	void ToBinary(const T* _objs, uint32 _size, std::string& _str);

//}


//{ From Binary

	template <typename T>
	T FromBinary(Reader& _read);

	template <typename T>
	void FromBinary(T& _obj, Reader& _read);

	template <typename T>
	void FromBinary(T* _objs, uint32 _size, Reader& _read);

//}
}

#include <SA/Core/Serialize/Serializer.inl>
#include <SA/Core/Serialize/StringSerializer.inl>
#include <SA/Core/Serialize/VectorSerializer.inl>
#include <SA/Core/Serialize/MapSerializer.inl>

#endif // GUARD
