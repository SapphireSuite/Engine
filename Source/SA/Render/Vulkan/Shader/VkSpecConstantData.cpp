// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Shader/VkSpecConstantData.hpp>

#include <Collections/Debug>

#if SA_VULKAN

namespace Sa::Vk
{
	void SpecConstantData::Add(const SpecConstantDescriptor& _desc)
	{
		if (_desc.value == nullptr)
		{
			SA_LOG(L"Try add descriptor with null value!", Warning, SA/Render/Vulkan);
			return;
		}

		Add(_desc.id, _desc.value->size, _desc.value->Data());
	}


	void SpecConstantData::Add(uint32 _id, uint32 _size, const void* _data)
	{
		const uint32 oldSize = SizeOf<uint32>(data);

		data.resize(oldSize + _size);
		std::memcpy(&data[oldSize], _data, _size);


		VkSpecializationMapEntry& entry = entries.emplace_back();
		entry.constantID = _id;
		entry.size = _size;
		entry.offset = oldSize;


		// Re-fill infos in case vector had re-allocate.
		FillSpecInfos();
	}


	void SpecConstantData::FillSpecInfos()
	{
		specInfo.mapEntryCount = SizeOf<uint32>(entries);
		specInfo.pMapEntries = entries.data();
		specInfo.dataSize = SizeOf<uint32>(data);
		specInfo.pData = data.data();
	}
}

#endif