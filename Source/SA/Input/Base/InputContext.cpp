// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/InputContext.hpp>

namespace Sa
{
	InputContext::~InputContext()
	{
		for (auto it = mKeyMap.begin(); it != mKeyMap.end(); ++it)
			delete it->second;

		for (auto it = mAxisMap.begin(); it != mAxisMap.end(); ++it)
			delete it->second;
	}

	void InputContext::UnBind(const InputKey& _inKey)
	{
		auto it = mKeyMap.find(_inKey);
		SA_WARN(it != mKeyMap.end(), SA/Input, L"Input key [" << _inKey << "] not previously bound!");

		delete it->second;

		mKeyMap.erase(it);
	}

	void InputContext::UnBind(Axis _axis)
	{
		auto it = mAxisMap.find(_axis);
		SA_WARN(it != mAxisMap.end(), SA/Input, L"Input axis [" << _axis << "] not previously bound!");
		
		delete it->second;

		mAxisMap.erase(it);
	}


	bool InputContext::Process(const InputKey& _inKey)
	{
		if (!bEnabled)
			return false;

		auto it = mKeyMap.find(_inKey);

		// Action not bind.
		if (it == mKeyMap.end())
			return false;

		return it->second->Execute(_inKey.state);
	}
	
	bool InputContext::Process(const InputAxis& _inAxis)
	{
		if (!bEnabled)
			return false;

		auto it = mAxisMap.find(_inAxis.axis);

		// Action not bind.
		if (it == mAxisMap.end())
			return false;

		return it->second->Execute(_inAxis.value);
	}
}
