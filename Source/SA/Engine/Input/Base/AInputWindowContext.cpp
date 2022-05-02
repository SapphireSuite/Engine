// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#include <SA/Collections/Debug>

#include <Input/Base/AInputWindowContext.hpp>

namespace Sa
{
	void AInputWindowContext::Create(AWindow* _win)
	{
		HardwareInterface::Create();

		SA_ASSERT(Nullptr, SA/Engine/Input, _win);
	}

	void AInputWindowContext::Clear()
	{
		HardwareInterface::Clear();

		mContexts.clear();

		SA_LOG(L"Input Window Context cleared.", Infos, SA/Engine/Input);
	}

	
	InputContext* AInputWindowContext::CreateContext()
	{
		CheckCreated();

		return &mContexts.emplace_front();
	}
	
	bool AInputWindowContext::DestroyContext(const InputContext* _context)
	{
		CheckCreated();
		
		SA_ASSERT(Nullptr, SA/Engine/Input, _context, L"Destroy null InputContext");

		auto prevIt = mContexts.before_begin();

		for (auto it = mContexts.begin(); it != mContexts.end(); ++it)
		{
			if (&*it == _context)
			{
				mContexts.erase_after(prevIt);
				return true;
			}

			prevIt = it;
		}

		return false;
	}
}
