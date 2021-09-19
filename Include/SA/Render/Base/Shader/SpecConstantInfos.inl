// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
	template <typename T>
	void SpecConstantInfos::Add(uint32 _id, T _specConst)
	{
		const uint32 size = sizeof(_specConst);
		const uint32 oldSize = static_cast<uint32>(data.size());

		data.resize(oldSize + size);

		reinterpret_cast<T&>(data[oldSize]) = _specConst;

		Descriptor& desc = descs.emplace_back();
		desc.id = _id;
		desc.size = size;
	}
}
