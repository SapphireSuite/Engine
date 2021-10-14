// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/ECS/Systems/Render/RenderSystem.hpp>

namespace Sa
{
	ARenderInterface* RenderSystem::GetInterface() const noexcept
	{
		return mInterface;
	}

	void RenderSystem::Destroy()
	{
		SA_ASSERT(Nullptr, SA/SDK/ECS, mInterface, L"Destroy nullptr Render Interface!");

		mInterface->Destroy();
		delete mInterface;

		SA_LOG(L"Render System destroyed.", Infos, SA/SDK/ECS);
	}


	RenderSubSystem* RenderSystem::CreateSubSystem(const AGraphicDeviceInfos& _infos)
	{
		RenderSubSystem* const subSys = new RenderSubSystem();

		subSys->Create(mInterface, _infos);

		return subSys;
	}

	void RenderSystem::DestroySubSystem(RenderSubSystem* _subSys)
	{
		SA_ASSERT(Nullptr, SA/SDK/ECS, _subSys);

		_subSys->Destroy(mInterface);

		delete _subSys;
	}
}
