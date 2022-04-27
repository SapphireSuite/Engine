// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#include <SA/Collections/Debug>

#include <Input/Base/AInputWindowContext.hpp>

namespace Sa
{
	void AInputWindowContext::Create(AWindow* _win)
	{
		HardwareInterfaceBase::Create();

		SA_ASSERT(Nullptr, SA/Engine/Input, _win);
	}

	void AInputWindowContext::Clear()
	{
		HardwareInterfaceBase::Clear();

		mContexts.clear();
	}

	
	InputContext* AInputWindowContext::CreateContext()
	{
		return &mContexts.emplace_front();
	}
	
	bool AInputWindowContext::DestroyContext(const InputContext* _context)
	{
		SA_ASSERT(Nullptr, SA/Engine/Input, _context, L"Destroy null InputContext");

		for (auto it = mContexts.begin(); it != mContexts.end(); ++it)
		{
			if (&*it == _context)
			{
				mContexts.erase(it);
				return true;
			}
		}

		return false;
	}
}
