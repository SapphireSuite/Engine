// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/ECS/Systems/Render/RenderSubSystem.hpp>

#include <Render/Base/ARenderInterface.hpp>

namespace Sa
{
	ARenderSubInterface* RenderSubSystem::GetInterface() const noexcept
	{
		return mInterface;
	}


	void RenderSubSystem::Create(ARenderInterface* _mainIntf, const AGraphicDeviceInfos& _infos)
	{
		SA_ASSERT(Nullptr, SA/SDK/ECS, _mainIntf, L"Create Render SubInterface from nullptr Render Interface!");

		mInterface = _mainIntf->CreateSubInterface(_infos);
	}
	
	void RenderSubSystem::Destroy(ARenderInterface* _mainIntf)
	{
		SA_ASSERT(Nullptr, SA/SDK/ECS, mInterface, L"Destroy nullptr Render SubInterface!");

		_mainIntf->DestroySubInterface(mInterface);

		mInterface = nullptr;
	}
}
