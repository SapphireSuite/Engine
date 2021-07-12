// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/AInputWindowContext.hpp>

namespace Sa
{
	AInputWindowContext::~AInputWindowContext()
	{
		Clear();
	}


	InputContext* AInputWindowContext::Create()
	{
		return mContexts.emplace_back(new InputContext);
	}

	bool AInputWindowContext::Destroy(const InputContext* _context)
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


	void AInputWindowContext::Clear()
	{
		for (auto it = mContexts.begin(); it != mContexts.end(); ++it)
		{
			SA_ASSERT(Nullptr, SA/Input, *it, L"Destroy null InputContext");

			delete *it;
		}

		mContexts.clear();
	}
}
