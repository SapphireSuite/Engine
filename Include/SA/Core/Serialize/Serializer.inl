// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa::Serialize
{
//{ To Binary

	template <typename T>
	std::string ToBinary(const T& _obj)
	{
		std::string res;

		ToBinary(_obj, res);

		return res;
	}

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
	T FromBinary(Reader& _read)
	{
		T res;

		FromBinary(res, _read);

		return res;
	}

	template <typename T>
	void FromBinary(T& _obj, Reader& _read)
	{
		Intl::FromBinary(&_obj, sizeof(T), _read);
	}

	template <typename T>
	void FromBinary(T* _objs, uint32 _size, Reader& _read)
	{
		if (Specs<T>::bContinuousData)
			Intl::FromBinary(_objs, sizeof(T) * _size, _read);
		else
		{
			for (auto it = _objs; it != _objs + _size; ++it)
				FromBinary(*it, _read);
		}
	}

//}
}
