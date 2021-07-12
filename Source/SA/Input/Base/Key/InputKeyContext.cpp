// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Key/InputKeyContext.hpp>

namespace Sa
{
	void InputKeyContext::UnBind(const InputKeyBind& _inKeyBind)
	{
		if (_inKeyBind.stateFlags & KeyState::Pressed)
			UnBind(InputKey{ _inKeyBind.key, KeyState::Pressed });

		if (_inKeyBind.stateFlags & KeyState::Released)
			UnBind(InputKey{ _inKeyBind.key, KeyState::Released });

		if (_inKeyBind.stateFlags & KeyState::Hold)
			UnBind(InputKey{ _inKeyBind.key, KeyState::Hold });
	}
	
	void InputKeyContext::UnBind(const InputKey& _inKey)
	{
		auto it = mMap.find(_inKey);

		if (it == mMap.end())
		{
			SA_LOG(L"Input key [" << _inKey << "] not previously bound!", Warning, SA/Input);
			return;
		}

		mMap.erase(it);
	}
	
	void InputKeyContext::UnBind(std::shared_ptr<InputKeyBinding> _inBinding)
	{
		for (auto itBinds = mMap.begin(); itBinds != mMap.end(); ++itBinds)
		{
			for (auto it = itBinds->second.begin(); it != itBinds->second.end();)
			{
				if (*it == _inBinding)
					it = itBinds->second.erase(it);
				else
					++it;
			}
		}
	}

	bool InputKeyContext::Process(const InputKey& _inKey)
	{
		auto itBinds = mMap.find(_inKey);

		// Action not bind.
		if (itBinds == mMap.end())
			return false;

		bool bRes = false;

		for (auto it = itBinds->second.begin(); it != itBinds->second.end(); ++it)
			bRes |= (*it)->Execute(_inKey.state);

		return bRes;
	}
}
