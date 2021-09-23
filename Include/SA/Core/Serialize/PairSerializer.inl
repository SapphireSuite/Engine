// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <utility>

namespace Sa::Serialize
{
	template <typename T1, typename T2>
	void ToBinary(const std::pair<T1, T2>& _obj, std::string& _str)
	{
		ToBinary(_obj.first, _str);
		ToBinary(_obj.second, _str);
	}

	template <typename T1, typename T2>
	void FromBinary(std::pair<T1, T2>& _obj, Reader& _read)
	{
		FromBinary(_obj.first, _read);
		FromBinary(_obj.second, _read);
	}
}
