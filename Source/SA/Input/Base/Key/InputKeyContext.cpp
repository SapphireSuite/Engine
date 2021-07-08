// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/Base/Key/InputKeyContext.hpp>

namespace Sa
{
	void InputKeyContext::UnBind(const InputKey& _inKey)
	{
		if (_inKey.stateFlags & KeyState::Pressed)
			UnBind(InputRawKey{ _inKey.key, KeyState::Pressed });

		if (_inKey.stateFlags & KeyState::Released)
			UnBind(InputRawKey{ _inKey.key, KeyState::Released });

		if (_inKey.stateFlags & KeyState::Hold)
			UnBind(InputRawKey{ _inKey.key, KeyState::Hold });
	}
	
	void InputKeyContext::UnBind(const InputRawKey& _inRawKey)
	{
		auto it = mMap.find(_inRawKey);

		if (it == mMap.end())
		{
			SA_LOG(L"Input key [" << _inRawKey << "] not previously bound!", Warning, SA/Input);
			return;
		}

		mMap.erase(it);
	}
	
	void InputKeyContext::UnBind(std::shared_ptr<InputKeyBinding> _inBinding)
	{
		for (auto itBinds = mMap.begin(); itBinds != mMap.end(); ++itBinds)
		{
			for (auto it = itBinds->second.begin(); it != itBinds->second.end(); ++it)
			{
				if (_inBinding == *it)
					itBinds->second.erase(it--);
			}
		}
	}

	bool InputKeyContext::Process(const InputRawKey& _inRawKey)
	{
		auto itBinds = mMap.find(_inRawKey);

		// Action not bind.
		if (itBinds == mMap.end())
			return false;

		bool bRes = false;

		for (auto it = itBinds->second.begin(); it != itBinds->second.end(); ++it)
			bRes |= (*it)->Execute(_inRawKey.state);

		return bRes;
	}
}
