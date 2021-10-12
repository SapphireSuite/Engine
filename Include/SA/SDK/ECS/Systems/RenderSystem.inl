// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename IntfT>
	void RenderSystem::Create(const WindowSystem& _winSys)
	{
		mInterface = new IntfT();
		mInterface->Create(_winSys.GetInterface());
	}
}
