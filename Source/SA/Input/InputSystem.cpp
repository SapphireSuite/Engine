// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/InputSystem.hpp>

#include <Collections/Debug>

namespace Sa
{
	InputSystem::~InputSystem()
	{
		Clear();
	}


	InputContext* InputSystem::CreateContext()
	{
		return mContexts.emplace_back(new InputContext);
	}

	void InputSystem::DestroyContext(InputContext* _context)
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


	void InputSystem::Clear()
	{
		for (auto it = mContexts.begin(); it != mContexts.end(); ++it)
			delete* it;

		mContexts.clear();
	}


	bool InputSystem::Process(const InputAction& _action)
	{
		// Find first context that can consume the input.

		for (auto it = mContexts.begin(); it != mContexts.end(); ++it)
		{
			if ((*it)->Process(_action))
				return true;
		}

		return false;
	}
}
