// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T>
	SpecConstant<T>::SpecConstant(T _data) noexcept :
		SpecConstantBase(sizeof(_data)),
		data{ _data }
	{
	}

	template <typename T>
	const void* SpecConstant<T>::Data() const
	{
		return &data;
	}
}
