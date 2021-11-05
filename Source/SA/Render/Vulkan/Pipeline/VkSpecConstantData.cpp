// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/VkSpecConstantData.hpp>

#include <Collections/Debug>

#include <Core/Algorithms/SizeOf.hpp>

namespace Sa::Vk
{
	void SpecConstantData::Add(const PipelineSpecConstant& _specCst)
	{
		if (_specCst.value == nullptr)
		{
			SA_LOG(L"Try add specialization constant with null value!", Warning, SA/Render/Vulkan);
			return;
		}

		Add(_specCst.id, _specCst.value->size, _specCst.value->Data());
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
