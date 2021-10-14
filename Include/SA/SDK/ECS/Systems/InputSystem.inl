// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename IntfT>
	IntfT* InputSystem::Create()
	{
		IntfT* interfaceT = new IntfT();

		mInterface = interfaceT;
		mInterface->Create();
		
		SA_LOG(L"Input System created.", Infos, SA/SDK/ECS);

		return interfaceT;
	}
}
