// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/AInputSystem.hpp>

#include <Collections/Debug>

namespace Sa
{
	AInputSystem::~AInputSystem()
	{
		Clear();
	}


	void AInputSystem::DestroyWindowContext(AInputWindowContext* _winContext)
	{
		SA_ASSERT(Nullptr, SA/Input, _winContext, L"Destroy null window context!");

		delete _winContext;
	}


	AInputWindowContext* AInputSystem::Register(AWindow* _win)
	{
		SA_ASSERT(Nullptr, SA/Input, _win, L"Register null window!");

		auto itFind = mWindowContextMap.find(_win);

		if (itFind != mWindowContextMap.end())
		{
			SA_LOG(L"Window already registered in System.", Warning, SA/Input);
			return itFind->second;
		}

		AInputWindowContext* const winContext = InstantiateWindowContext(_win);

		mWindowContextMap.emplace(_win, winContext);

		return winContext;
	}

	bool AInputSystem::UnRegister(const AWindow* _win)
	{
		SA_ASSERT(Nullptr, SA/Input, _win, L"UnRegister null window!");

		auto itFind = mWindowContextMap.find(_win);

		if (itFind == mWindowContextMap.end())
		{
			SA_LOG(L"Unregister a Window not previously registered in System.", Warning, SA/Input);
			return false;
		}

		DestroyWindowContext(itFind->second);
		mWindowContextMap.erase(itFind);

		return true;
	}


	void AInputSystem::Clear()
	{
		for (auto it = mWindowContextMap.begin(); it != mWindowContextMap.end(); ++it)
			delete it->second;

		mWindowContextMap.clear();
	}
}
