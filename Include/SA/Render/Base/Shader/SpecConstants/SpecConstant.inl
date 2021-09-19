// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T>
	SpecConstant<T>::SpecConstant(uint32 _id, T _data) noexcept :
		SpecConstantBase(_id, sizeof(_data)),
		data{ _data }
	{
	}

	template <typename T>
	const void* SpecConstant<T>::Data() const
	{
		return &data;
	}
}
