// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename InBindT>
	void InputContext::Bind(const InputKey& _inKey, InBindT _binding)
	{
		SA_WARN(mKeyMap.find(_inKey) == mKeyMap.end(), SA/Input, L"Input key [" << _inKey << "] already bound!");

		mKeyMap.emplace(_inKey, new InBindT{ std::move(_binding) });
	}

	template <typename InBindT>
	void InputContext::Bind(Axis _axis, InBindT _binding)
	{
		SA_WARN(mAxisMap.find(_axis) == mAxisMap.end(), SA/Input, L"Input axis [" << _axis << "] already bound!");

		mAxisMap.emplace(_axis, new InBindT{ std::move(_binding) });
	}
}
