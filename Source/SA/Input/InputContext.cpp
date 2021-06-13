// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/InputContext.hpp>

namespace Sa
{
	void InputContext::BindAction(InputAction _action, Function<void()> _func)
	{
		SA_WARN(mActionMap.find(_action) == mActionMap.end(), SA/Input, L"Input action [" << _action << "] already bound!");

		mActionMap.emplace(_action, std::move(_func));
	}

	void InputContext::UnBindAction(InputAction _action)
	{
		auto it = mActionMap.find(_action);
		SA_WARN(it != mActionMap.end(), SA/Input, L"Input key [" << _action << "] not previously bound!");

		mActionMap.erase(it);
	}


	bool InputContext::Process(const InputAction& _action)
	{
		auto it = mActionMap.find(_action);

		// Action not bind.
		if (it == mActionMap.end())
			return false;

		it->second.Execute();

		return true;
	}
}
