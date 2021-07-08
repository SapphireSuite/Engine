// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Contexts/InputContext.hpp>

namespace Sa
{
	InputContext::~InputContext()
	{
		for (auto it = mAxisMap.begin(); it != mAxisMap.end(); ++it)
			delete it->second;
	}


	void InputContext::UnBind(Axis _axis)
	{
		auto it = mAxisMap.find(_axis);
		SA_WARN(it != mAxisMap.end(), SA/Input, L"Input axis [" << _axis << "] not previously bound!");
		
		delete it->second;

		mAxisMap.erase(it);
	}


	bool InputContext::Process(const InputRawKey& _inRawKey)
	{
		if (!bEnabled)
			return false;

		return key.Process(_inRawKey);
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
