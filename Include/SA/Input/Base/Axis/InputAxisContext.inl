// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename InBindT, typename... Args>
	std::shared_ptr<InputAxisBinding> InputAxisContext::Bind(const InputAxisBind& _inAxisBind, Args&&... _args)
	{
		SA_ASSERT(Default, SA/Input, _inAxisBind.axis != Axis::None, L"Can't bind \'None\' Axis!");

		std::shared_ptr<InputAxisBinding> bindPtr = std::static_pointer_cast<InputAxisBinding>(
			std::make_shared<InBindT>(std::forward<Args>(_args)...));

		mMap[_inAxisBind.axis].push_back(bindPtr);

		return bindPtr;
	}
}
