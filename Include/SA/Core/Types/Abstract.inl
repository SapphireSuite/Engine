// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T>
	T& Abstract::As()
	{
		SA_ASSERT(Nullptr, SA/Core, dynamic_cast<T*>(this), L"Interface is not of type T");

		return reinterpret_cast<T&>(*this);
	}

	template <typename T>
	const T& Abstract::As() const
	{
		SA_ASSERT(Nullptr, SA/Core, dynamic_cast<const T*>(this), L"Interface is not of type T");

		return reinterpret_cast<const T&>(*this);
	}

	template <typename T>
	T* Abstract::AsPtr()
	{
		SA_ASSERT(Nullptr, SA/Core, dynamic_cast<T*>(this), L"Interface is not of type T");

		return reinterpret_cast<T*>(this);
	}

	template <typename T>
	const T* Abstract::AsPtr() const
	{
		SA_ASSERT(Nullptr, SA/Core, dynamic_cast<const T*>(this), L"Interface is not of type T");

		return reinterpret_cast<const T*>(this);
	}
}
