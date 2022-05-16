// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

namespace SA
{
	template <typename... Args>
	template <typename FindT, typename FirstT, typename... PArgs>
	uint32_t Vertex<Args...>::GetComponentOffsetPacked() noexcept
	{
		if constexpr (std::is_same<FirstT, FindT>::value)
			return 0u;
		else if constexpr (sizeof...(PArgs) != 0)
			return sizeof(FirstT) + GetComponentOffsetPacked<FindT, PArgs...>();
	}

	template <typename... Args>
	template <typename T>
	uint32_t Vertex<Args...>::GetComponentOffset() noexcept
	{
        static_assert(std::is_base_of<T, Vertex>::value, "Component is not a part of Vertex");

		return GetOffsetPacked<T, Args...>();
	}
}
