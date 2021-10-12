// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/ECS/Systems/RenderSystem.hpp>

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
	}
}
