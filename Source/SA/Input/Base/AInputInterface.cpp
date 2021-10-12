// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/AInputInterface.hpp>

#include <Core/Debug.hpp>

namespace Sa
{
	AInputInterface::~AInputInterface()
	{
		Clear();
	}


	AInputWindowContext* AInputInterface::Register(AWindow* _win)
	{
		SA_ASSERT(Nullptr, SA/Input, _win, L"Register null window!");

		auto itFind = mWindowContextMap.find(_win);

		if (itFind != mWindowContextMap.end())
		{
			SA_LOG(L"Window already registered in System.", Warning, SA/Input);
			return itFind->second;
		}

		AInputWindowContext* const winContext = InstantiateWindowContext();
		winContext->Create(_win);

		mWindowContextMap.emplace(_win, winContext);

		return winContext;
	}

	bool AInputInterface::UnRegister(const AWindow* _win)
	{
		SA_ASSERT(Nullptr, SA/Input, _win, L"UnRegister null window!");

		auto itFind = mWindowContextMap.find(_win);

		if (itFind == mWindowContextMap.end())
		{
			SA_LOG(L"Unregister a Window not previously registered in System.", Warning, SA/Input);
			return false;
		}

		itFind->second->Destroy();
		DeleteWindowContext(itFind->second);

		mWindowContextMap.erase(itFind);

		return true;
	}


	void AInputInterface::Clear()
	{
		for (auto it = mWindowContextMap.begin(); it != mWindowContextMap.end(); ++it)
		{
			it->second->Destroy();
			DeleteWindowContext(it->second);
		}

		mWindowContextMap.clear();
	}


	void AInputInterface::Destroy()
	{
		Clear();
	}
}
