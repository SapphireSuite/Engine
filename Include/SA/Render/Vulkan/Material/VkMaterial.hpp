// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_MATERIAL_GUARD
#define SAPPHIRE_RENDER_VK_MATERIAL_GUARD

#include <SA/Render/Base/Material/ARenderMaterial.hpp>

#include <SA/Render/Vulkan/Pipeline/VkDescriptorSet.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Material : public ARenderMaterial
	{
		DescriptorSet mDescSet;

	public:
		void Create(const ARenderDevice* _device,
			const ARenderPipeline* _pipeline,
			const RenderPipelineCreateInfos& _infos,
			uint32 setIndex = 0) override final;
		void Destroy(const ARenderDevice* _device) override final;
	};
}

#endif

#endif // GUARD
