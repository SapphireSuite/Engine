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


/**
*	Helper macro to serialize only a block inside an object.
* 
*	\param _method	The serialization method to use (can be either To or From).
*	\param _obj		Object to read data from.
*	\param _begin	The begin member of _obj to serialize data from.
*	\param _end		The end member of _obj to serialize data to.
*	\param _str		Current string / reader to use.
*/
#define SA_SerializeBlock(_method, _obj, _begin, _end, _str)\
	Sa::Serialize::Intl::_method(&_obj._begin,\
	offsetof(std::remove_reference<decltype(_obj)>::type, _end) - offsetof(std::remove_reference<decltype(_obj)>::type, _begin),\
	_str);

/**
*	Helper macro to serialize only a block inside an object.
*
*	\param _method	The serialization method to use (can be either To or From).
*	\param _obj		Object to read data from.
*	\param _begin	The begin member of _obj to serialize data from.
*	\param _str		Current string / reader to use.
*/
#define SA_SerializeEndBlock(_method, _obj, _begin, _str)\
	Sa::Serialize::Intl::_method(&_obj._begin,\
	sizeof(std::remove_reference<decltype(_obj)>::type) - offsetof(std::remove_reference<decltype(_obj)>::type, _begin),\
	_str);


#include <SA/Core/Serialize/StringSerializer.inl>
#include <SA/Core/Serialize/VectorSerializer.inl>
#include <SA/Core/Serialize/SetSerializer.inl>
#include <SA/Core/Serialize/MapSerializer.inl>
#include <SA/Core/Serialize/Serializer.inl>

#endif // GUARD
