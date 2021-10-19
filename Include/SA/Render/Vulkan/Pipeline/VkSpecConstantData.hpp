// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SPEC_CONSTANT_DATA_GUARD
#define SAPPHIRE_RENDER_VK_SPEC_CONSTANT_DATA_GUARD

#include <SA/Render/Base/Shader/SpecConstants/DefaultSpecConstant.hpp>
#include <SA/Render/Base/Pipeline/PipelineShaderInfos.hpp>

namespace Sa::Vk
{
	class SpecConstantData
	{
		void FillSpecInfos();

	public:
		VkSpecializationInfo specInfo;
		std::vector<VkSpecializationMapEntry> entries;

		std::vector<char> data;

		void Add(const PipelineSpecConstant& _specCst);
		void Add(uint32 _id, uint32 _size, const void* _data);

		template <typename T>
		void Add(uint32 _id, T _data)
		{
			Add(_id, sizeof(T), &_data);
		}
	};
}

#endif // GUARD
