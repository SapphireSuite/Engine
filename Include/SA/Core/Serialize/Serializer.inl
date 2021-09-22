// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa::Serialize
{
//{ To Binary

	template <typename T>
	void ToBinary(const T& _obj, std::string& _str)
	{
		Intl::ToBinary(&_obj, sizeof(T), _str);
	}

	template <typename T>
	void ToBinary(const T* _objs, uint32 _size, std::string& _str)
	{
		ToBinary(_size, _str);

		if (Specs<T>::bContinuousData)
			Intl::ToBinary(_objs, sizeof(T) * _size, _str);
		else
		{
			for (auto it = _objs; it != _objs + _size; ++it)
				ToBinary(*it, _str);
		}
	}

//}


//{ From Binary

	template <typename T>
	void FromBinary(std::string& _str, T& _obj)
	{
		Intl::FromBinary(_str, &_obj, sizeof(T));
	}

	template <typename T>
	void FromBinary(std::string& _str, T* _objs, uint32 _size)
	{
		if (Specs<T>::bContinuousData)
			Intl::FromBinary(_str, _objs, sizeof(T) * _size);
		else
		{
			for (auto it = _objs; it != _objs + _size; ++it)
				FromBinary(_str, *it);
		}
	}

//}
}
