// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/InputContext.hpp>

namespace Sa
{
	InputContext::~InputContext()
	{
		for (auto it = mKeyMap.begin(); it != mKeyMap.end(); ++it)
			delete it->second;

		//for (auto it = mAxisMap.begin(); it != mAxisMap.end(); ++it)
		//	delete it->second;

		//for (auto it = mCompositeMap.begin(); it != mCompositeMap.end(); ++it)
		//	delete it->second;
	}


	void InputContext::Bind(const InputKey& _inKey, InputAction _action)
	{
		SA_WARN(mKeyMap.find(_inKey) == mKeyMap.end(), SA/Input, L"Input key [" << _inKey << "] already bound!");

		mKeyMap.emplace(_inKey, new InputAction{ std::move(_action) });
	}

	/*
	void InputContext::Bind(const InputAxis& _inAxis, InputAction _action)
	{
		SA_WARN(mAxisMap.find(_inAxis) == mAxisMap.end(), SA/Input, L"Input axis [" << _inAxis << "] already bound!");

		mAxisMap.emplace(_inAxis, std::move(_action));
	}

	void InputContext::Bind(InputComposite _inComp, InputAction _action)
	{
		SA_WARN(mCompositeMap.find(_inComp) == mCompositeMap.end(), SA/Input, L"Input composite [" << _inComp << "] already bound!");

		mCompositeMap.emplace(std::move(_inComp), std::move(_action));
	}
	*/

	void InputContext::UnBind(const InputKey& _inKey)
	{
		auto it = mKeyMap.find(_inKey);
		SA_WARN(it != mKeyMap.end(), SA/Input, L"Input key [" << _inKey << "] not previously bound!");

		delete it->second;

		mKeyMap.erase(it);
	}

	/*
	void InputContext::UnBind(const InputAxis& _inAxis)
	{
		auto it = mAxisMap.find(_inAxis);
		SA_WARN(it != mAxisMap.end(), SA / Input, L"Input axis [" << _inAxis << "] not previously bound!");
		
		delete it->second;

		mAxisMap.erase(it);
	}

	void InputContext::UnBind(const InputComposite& _inComp)
	{
		auto it = mCompositeMap.find(_inComp);
		SA_WARN(it != mCompositeMap.end(), SA / Input, L"Input composite [" << _inComp << "] not previously bound!");
		
		delete it->second;

		mCompositeMap.erase(it);
	}
	*/

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
	
	/*
	bool InputContext::Process(const InputAxis& _inAxis)
	{
		if (!bEnabled)
			return false;

		auto it = mAxisMap.find(_inAxis);

		// Action not bind.
		if (it == mAxisMap.end())
			return false;

		return it->second->Execute(_inAxis.value);
	}
	
	bool InputContext::Process(const InputComposite& _inComp)
	{
		if (!bEnabled)
			return false;

		auto it = mCompositeMap.find(_inComp);

		// Action not bind.
		if (it == mCompositeMap.end())
			return false;

		// TODO: Implement.
		//return it->second->Execute();
		return false;
	}
	*/
}
