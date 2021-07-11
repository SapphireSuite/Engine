// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/IInputWindowContext.hpp>

namespace Sa
{
	IInputWindowContext::~IInputWindowContext()
	{
		Clear();
	}


	InputContext* IInputWindowContext::Create()
	{
		return mContexts.emplace_back(new InputContext);
	}

	bool IInputWindowContext::Destroy(const InputContext* _context)
	{
		SA_ASSERT(Nullptr, SA/Input, _context, L"Destroy null InputContext");

		for (auto it = mContexts.begin(); it != mContexts.end(); ++it)
		{
			if (*it == _context)
			{
				mContexts.erase(it);
				return true;
			}
		}

		return false;
	}


	void IInputWindowContext::Clear()
	{
		for (auto it = mContexts.begin(); it != mContexts.end(); ++it)
		{
			SA_ASSERT(Nullptr, SA/Input, *it, L"Destroy null InputContext");

			delete *it;
		}

		mContexts.clear();
	}
}
