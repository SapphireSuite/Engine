// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Shader/VkSpecConstantData.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	SpecConstantData::SpecConstantData(const SpecConstantInfos& _infos)
	{
		uint32 offset = 0u;

		for (auto it = _infos.specConsts.begin(); it != _infos.specConsts.end(); ++it)
		{
			const uint32 size = (*it)->size;


			// Create vk entry.
			{
				VkSpecializationMapEntry& entry = entries.emplace_back();
				entry.constantID = (*it)->id;
				entry.size = size;
				entry.offset = offset;
			}


			// Copy data.
			{
				uint32 oldSize = SizeOf<uint32>(data);
				data.resize(data.size() + size);
				std::memcpy(data.data() + oldSize, (*it)->Data(), size);
			}

			offset += size;
		}


		// API Spec.
		Add(SpecConstantID::RenderAPI, SpecConstantValue::Vulkan);


		// Called  by Add.
		//FillSpecInfos();
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
