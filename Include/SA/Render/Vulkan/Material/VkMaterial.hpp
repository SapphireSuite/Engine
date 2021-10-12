// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_MATERIAL_GUARD
#define SAPPHIRE_RENDER_VK_MATERIAL_GUARD

#include <SA/Render/Base/Material/ARenderMaterial.hpp>

#include <SA/Render/Vulkan/Pipeline/VkDescriptorSet.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class Material : public ARenderMaterial
	{
		DescriptorSet mDescSet;

	public:
		void Create(const Device& _device, const RenderMaterialCreateInfos& _infos);
		void Destroy(const Device& _device);

		void UpdateBinding(const Device& _device, const ARenderMaterialBinding* _bind);
	};
}

#endif

#endif // GUARD
