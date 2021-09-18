// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T, typename... Args>
	void DescriptorSetCreateInfos::AddBinding(Args&&... _args)
	{
		bindings.emplace_back(new T(std::forward<Args>(_args)...));
	}
}
