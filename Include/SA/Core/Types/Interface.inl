// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T>
	T& Interface::As()
	{
		SA_ASSERT(Nullptr, Core, dynamic_cast<T*>(this), L"Interface is not of type T");

		return reinterpret_cast<T&>(*this);
	}

	template <typename T>
	const T& Interface::As() const
	{
		SA_ASSERT(Nullptr, Core, dynamic_cast<const T*>(this), L"Interface is not of type T");

		return reinterpret_cast<const T&>(*this);
	}

	template <typename T>
	T* Interface::AsPtr()
	{
		SA_ASSERT(Nullptr, Core, dynamic_cast<T*>(this), L"Interface is not of type T");

		return reinterpret_cast<T*>(this);
	}

	template <typename T>
	const T* Interface::AsPtr() const
	{
		SA_ASSERT(Nullptr, Core, dynamic_cast<const T*>(this), L"Interface is not of type T");

		return reinterpret_cast<const T*>(this);
	}
}
