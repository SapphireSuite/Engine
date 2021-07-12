// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename InBindT, typename... Args>
	std::shared_ptr<InputKeyBinding> InputKeyContext::Bind(const InputKeyBind& _inKeyBind, Args&&... _args)
	{
		SA_ASSERT(Default, SA/Input, _inKeyBind.stateFlags, L"Can't bind input with no state!");

		std::shared_ptr<InputKeyBinding> bindPtr = std::static_pointer_cast<InputKeyBinding>(
				std::make_shared<InBindT>(std::forward<Args>(_args)...));

		if (_inKeyBind.stateFlags & KeyState::Pressed)
			mMap[InputKey{ _inKeyBind.key, KeyState::Pressed }].push_back(bindPtr);

		if (_inKeyBind.stateFlags & KeyState::Released)
			mMap[InputKey{ _inKeyBind.key, KeyState::Released }].push_back(bindPtr);

		if (_inKeyBind.stateFlags & KeyState::Hold)
			mMap[InputKey{ _inKeyBind.key, KeyState::Hold }].push_back(bindPtr);

		return bindPtr;
	}
}
