// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T>
	void SpecConstantInfos::Add(uint32 _id, T _specConst)
	{
		specConsts.emplace_back(new SpecConstant<T>(_id, _specConst));
	}
}
