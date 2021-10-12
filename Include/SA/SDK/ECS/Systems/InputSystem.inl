// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename IntfT>
	void InputSystem::Create()
	{
		mInterface = new IntfT();
		mInterface->Create();
	}
}
