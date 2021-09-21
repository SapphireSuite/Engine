// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SPEC_CONSTANT_DATA_GUARD
#define SAPPHIRE_RENDER_VK_SPEC_CONSTANT_DATA_GUARD

#include <vector>

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Core/Algorithms/SizeOf.hpp>

#include <SA/Render/Base/Shader/SpecConstants/DefaultSpecConstant.hpp>
#include <SA/Render/Base/Shader/SpecConstants/SpecConstantDescriptor.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class SpecConstantData
	{
		void FillSpecInfos();

	public:
		VkSpecializationInfo specInfo;
		std::vector<VkSpecializationMapEntry> entries;

		std::vector<char> data;

		void Add(const SpecConstantDescriptor& _desc);
		void Add(uint32 _id, uint32 _size, const void* _data);

		template <typename T>
		void Add(uint32 _id, T _data)
		{
			Add(_id, sizeof(T), &_data);
		}
	};
}

#endif

#endif // GUARD
