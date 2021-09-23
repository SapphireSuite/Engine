// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T, typename... Args>
	T* DescriptorSetCreateInfos::AddBinding(Args&&... _args)
	{
		T* const binding = new T(std::forward<Args>(_args)...);

		bindings.emplace_back(binding);

		return binding;
	}
}
