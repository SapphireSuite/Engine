// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename IntfT>
	void WindowSystem::Create()
	{
		mInterface = new IntfT();
		mInterface->Create();
	}
}
