// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Material/VkMaterial.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pipeline/VkPipeline.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void Material::Create(const Device& _device, const RenderMaterialCreateInfos& _infos)
	{
		const Pipeline& vkPipeline = _infos.pipeline->As<Pipeline>();

		SA_ASSERT(Nullptr, SA/Render/Vulkan, _infos.desc, L"Create render material witn nullptr pipeline descriptor.");
		SA_ASSERT(OutOfRange, SA/Render/Vulkan, _infos.setIndex, 0u, (uint32)_infos.desc->shaderInfos.bindingSets.size(), L"Set index is out of pipeline range!");

		mDescSet.Create(_device, _infos.desc->shaderInfos.bindingSets[_infos.setIndex], vkPipeline.GetDescriptorSetLayouts()[_infos.setIndex]);

		if(!_infos.bindings.empty())
			mDescSet.Update(_device, _infos.bindings);
		
		SA_LOG(L"Render Material created.", Infos, SA/Render/Vulkan);
	}

	void Material::Destroy(const Device& _device)
	{
		mDescSet.Destroy(_device);
		
		SA_LOG(L"Render Material destroyed.", Infos, SA/Render/Vulkan);
	}


	void Material::UpdateBinding(const Device& _device, const ARenderMaterialBinding* _bind)
	{
		mDescSet.Update(_device, { _bind });
	}
}

#endif
