// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_MATERIAL_GUARD
#define SAPPHIRE_ENGINE_VK_MATERIAL_GUARD

#include <SA/Engine/Render/Base/Material/ARenderMaterial.hpp>

#include <SA/Engine/Render/Vulkan/Material/VkDescriptorPool.hpp>

namespace SA
{
	struct RenderPipelineLayoutDescriptor;

	namespace VK
	{
		class Device;

		class Material : public ARenderMaterial
		{
			using ARenderMaterial::Create; // overloaded.
			using ARenderMaterial::Destroy; // overloaded.

			DescriptorPool mPool;
			std::vector<DescriptorSetLayout> mLayouts;
			std::vector<DescriptorSet> mSets;

			void CreateDescriptorPool(const Device& _device, const RenderPipelineLayoutDescriptor& _pipLayout);
			void DestroyDescriptorPool(const Device& _device);

			void CreateDescriptorSetLayouts(const Device& _device, const RenderPipelineLayoutDescriptor& _pipLayout);
			void DestroyDescriptorSetLayouts(const Device& _device);

		public:
			void Create(const Device& _device, const RenderPipelineLayoutDescriptor& _pipLayout);
			void Destroy(const Device& _device);
		};
	}
}

#endif // GUARD
