// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/ECS/Systems/WindowSystem.hpp>

namespace Sa
{
	AWindowInterface* WindowSystem::GetInterface() const noexcept
	{
		return mInterface;
	}

	void WindowSystem::Destroy()
	{
		SA_ASSERT(Nullptr, SA/SDK/ECS, mInterface, L"Destroy nullptr Window Interface!");

		mInterface->Destroy();
		delete mInterface;
	}
}
