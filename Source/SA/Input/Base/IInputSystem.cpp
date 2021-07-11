// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/IInputSystem.hpp>

#include <Collections/Debug>

namespace Sa
{
	IInputSystem::~IInputSystem()
	{
		Clear();
	}


	void IInputSystem::DestroyWindowContext(IInputWindowContext* _winContext)
	{
		SA_ASSERT(Nullptr, SA/Input, _winContext, L"Destroy null window context!");

		delete _winContext;
	}


	IInputWindowContext* IInputSystem::Register(IWindow* _win)
	{
		SA_ASSERT(Nullptr, SA/Input, _win, L"Register null window!");

		auto itFind = mWindowContextMap.find(_win);

		if (itFind != mWindowContextMap.end())
		{
			SA_LOG(L"Window already registered in System.", Warning, SA/Input);
			return itFind->second;
		}

		IInputWindowContext* const winContext = InstantiateWindowContext(_win);

		mWindowContextMap.emplace(_win, winContext);

		return winContext;
	}

	bool IInputSystem::UnRegister(const IWindow* _win)
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


	void IInputSystem::Clear()
	{
		for (auto it = mWindowContextMap.begin(); it != mWindowContextMap.end(); ++it)
			delete it->second;

		mWindowContextMap.clear();
	}
}
