// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename IntfT>
	IntfT* WindowSystem::Create()
	{
		IntfT* interfaceT = new IntfT();

		mInterface = interfaceT;
		mInterface->Create();

		SA_LOG(L"Window System created.", Infos, SA/SDK/ECS);

		return interfaceT;
	}
}
