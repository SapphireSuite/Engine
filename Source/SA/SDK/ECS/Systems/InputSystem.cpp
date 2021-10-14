// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SDK/ECS/Systems/InputSystem.hpp>

namespace Sa
{
	AInputInterface* InputSystem::GetInterface() const noexcept
	{
		return mInterface;
	}

	void InputSystem::Destroy()
	{
		SA_ASSERT(Nullptr, SA/SDK/ECS, mInterface, L"Destroy nullptr Input Interface!");

		mInterface->Destroy();
		delete mInterface;

		SA_LOG(L"Input System destroyed.", Infos, SA/SDK/ECS);
	}


	void InputSystem::Update()
	{
		mInterface->Update();
	}
}
