// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename InBindT, typename... Args>
	std::shared_ptr<InputKeyBinding> InputKeyContext::Bind(const InputKey& _inKey, Args&&... _args)
	{
		SA_ASSERT(Default, SA/Input, _inKey.stateFlags, L"Can't bind input with no state!");

		std::shared_ptr<InputKeyBinding> bindPtr = std::static_pointer_cast<InputKeyBinding>(
				std::make_shared<InBindT>(std::forward<Args>(_args)...));

		if (_inKey.stateFlags & KeyState::Pressed)
			mMap[InputRawKey{ _inKey.key, KeyState::Pressed }].push_back(bindPtr);

		if (_inKey.stateFlags & KeyState::Released)
			mMap[InputRawKey{ _inKey.key, KeyState::Released }].push_back(bindPtr);

		if (_inKey.stateFlags & KeyState::Hold)
			mMap[InputRawKey{ _inKey.key, KeyState::Hold }].push_back(bindPtr);

		return bindPtr;
	}
}
