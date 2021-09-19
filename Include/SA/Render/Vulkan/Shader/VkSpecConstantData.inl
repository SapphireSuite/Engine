// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#if SA_VULKAN

namespace Sa::Vk
{
	template <typename T>
	void SpecConstantData::Add(SpecConstantID _id, T _specConst)
	{
		const uint32 size = sizeof(_specConst);
		const uint32 oldSize = SizeOf<uint32>(data);

		data.resize(oldSize + size);
		reinterpret_cast<T&>(data[oldSize]) = _specConst;


		VkSpecializationMapEntry& entry = entries.emplace_back();
		entry.constantID = static_cast<uint32>(_id);
		entry.size = size;
		entry.offset = oldSize;


		// Re-fill infos in case vector had re-allocate.
		FillSpecInfos();
	}
}

#endif
