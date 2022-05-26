// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_MATERIAL_GUARD
#define SAPPHIRE_ENGINE_VK_MATERIAL_GUARD

#include <SA/Engine/Render/Base/Material/ARenderMaterial.hpp>

#include <SA/Engine/Render/Vulkan/DescriptorSet/VkDescriptorPool.hpp>

namespace SA::VK
{
	class Device;
	class PipelineLayout;
	struct MaterialBindRecorder;

	class Material : public ARenderMaterial
	{
		using ARenderMaterial::Destroy; // overloaded.

		DescriptorPool mPool;
		std::vector<DescriptorSet> mSets;

		void CreateDescriptorPool(const Device& _device, const RenderPipelineLayoutDescriptor& _pipLayoutDesc);
		void DestroyDescriptorPool(const Device& _device);

		void ParseBinding(MaterialBindRecorder& _rec, const MaterialStaticBindingInfos& _infos, ARenderMaterialBinding* _binding);

	public:
		void Create(const Device& _device,
			const PipelineLayout& _pipLayout,
			const RenderPipelineLayoutDescriptor& _pipLayoutDesc,
			const MaterialBindingData& _bindData = MaterialBindingData());
		void Destroy(const Device& _device);

		void Bind(const Device& _device, const MaterialBindingData& _bindData);
	};
}

#endif // GUARD
