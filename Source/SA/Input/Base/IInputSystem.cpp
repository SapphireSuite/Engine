// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/IInputSystem.hpp>

#include <Collections/Debug>

namespace Sa
{
	IInputSystem::~IInputSystem()
	{
		Clear();
	}


	InputContext* IInputSystem::CreateContext()
	{
		return mContexts.emplace_back(new InputContext);
	}

	void IInputSystem::DestroyContext(InputContext* _context)
	{
		SA_ASSERT(Nullptr, SA/Input, _context);

		bool bFound = false;

		for (auto it = mContexts.begin(); it != mContexts.end(); ++it)
		{
			if (*it == _context)
			{
				mContexts.erase(it);
				bFound = true;
			}
		}

		(void)bFound;
		SA_WARN(bFound, SA/Input, L"Input context could not be found!");
	}


	void IInputSystem::Clear()
	{
		for (auto it = mContexts.begin(); it != mContexts.end(); ++it)
			delete* it;

		mContexts.clear();
	}


	bool IInputSystem::Process(const InputKey& _inKey)
	{
		// Process from last added context to older one.

		bool bSuccess = false;

		for (auto it = mContexts.rbegin(); it != mContexts.rend(); ++it)
		{
			if ((*it)->Process(_inKey))
			{
				bSuccess = true;

				// Consume input (no forward to next contexts).
				if ((*it)->mode == InputContext::ProcessMode::Consume)
					return true;
			}
		}

		return bSuccess;
	}
}
