// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Material/VkMaterial.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pipeline/VkPipeline.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void Material::Create(const ARenderDevice* _device,
		const ARenderPipeline* _pipeline,
		const RenderPipelineDescriptor& _desc,
		uint32 setIndex)
	{
		const Device& vkDevice = _device->As<Device>();
		const Pipeline& vkPipeline = _pipeline->As<Pipeline>();

		SA_ASSERT(OutOfRange, SA/Render/Vulkan, setIndex, 0u, (uint32)_desc.shaderInfos.bindingSets.size(), L"Set index is out of pipeline range!");

		mDescSet.Create(vkDevice, _desc.shaderInfos.bindingSets[setIndex], vkPipeline.GetDescriptorSetLayouts()[setIndex]);

		SA_LOG(L"Material created.", Infos, SA/Render/Vulkan);
	}

	void Material::Destroy(const ARenderDevice* _device)
	{
		const Device& vkDevice = _device->As<Device>();

		mDescSet.Destroy(vkDevice);

		SA_LOG(L"Material destroyed.", Infos, SA/Render/Vulkan);
	}
}

#endif
