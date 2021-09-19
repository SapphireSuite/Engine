// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SPEC_CONSTANT_DATA_GUARD
#define SAPPHIRE_RENDER_VK_SPEC_CONSTANT_DATA_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Core/Algorithms/SizeOf.hpp>

#include <SA/Render/Base/Shader/SpecConstants/SpecConstantInfos.hpp>

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


		SpecConstantData(const SpecConstantInfos& _infos);


		template <typename T>
		void Add(SpecConstantID _id, T _specConst);
	};
}

#include <SA/Render/Vulkan/Shader/VkSpecConstantData.inl>

#endif

#endif // GUARD
