// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename BindT, typename... Args>
	void RenderMaterialCreateInfos::AddBinding(Args&&... _args)
	{
		bindings.emplace_back(new BindT(std::forward<Args>(_args)...));
	}
}
