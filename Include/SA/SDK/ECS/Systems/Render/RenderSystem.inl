// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename IntfT>
	IntfT* RenderSystem::Create(const WindowSystem& _winSys)
	{
		IntfT* interfaceT = new IntfT();

		mInterface = interfaceT;
		mInterface->Create(_winSys.GetInterface());
		
		SA_LOG(L"Render System created.", Infos, SA/SDK/ECS);

		return interfaceT;
	}
}
