// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_SERIALIZER_GUARD
#define SAPPHIRE_CORE_SERIALIZER_GUARD

#include <string>

#include <SA/Core/Types/Int.hpp>

namespace Sa::Serialize
{
	namespace Intl
	{
		void ToBinary(const void* _data, uint32 _size, std::string& _str);
		void FromBinary(std::string& _str, void* _data, uint32 _size);
	}
		

	template <typename T>
	struct Specs
	{
		static constexpr bool bContinuousData = std::is_arithmetic<T>::value;
	};


//{ To Binary

	template <typename T>
	void ToBinary(const T& _obj, std::string& _str);

	template <typename T>
	void ToBinary(const T* _objs, uint32 _size, std::string& _str);

//}


//{ From Binary

	template <typename T>
	void FromBinary(std::string& _str, T& _obj);

	template <typename T>
	void FromBinary(std::string& _str, T* _objs, uint32 _size);

//}
}

#include <SA/Core/Serialize/Serializer.inl>

#endif // GUARD
