// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename InBindT>
	void InputContext::Bind(Axis _axis, InBindT _binding)
	{
		SA_WARN(mAxisMap.find(_axis) == mAxisMap.end(), SA/Input, L"Input axis [" << _axis << "] already bound!");

		mAxisMap.emplace(_axis, new InBindT{ std::move(_binding) });
	}
}
