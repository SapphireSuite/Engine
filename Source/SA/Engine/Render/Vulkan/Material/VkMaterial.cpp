// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Material/VkMaterial.hpp>

#include <Render/Base/Pipeline/Descriptors/RenderPipelineLayoutDescriptor.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace SA::VK
{
	void Material::CreateDescriptorPool(const Device& _device, const RenderPipelineLayoutDescriptor& _pipLayout)
	{
		DescriptorPoolInfos infos;

		for (auto it = _pipLayout.bindSetDescs.begin(); it != _pipLayout.bindSetDescs.end(); ++it)
			infos.AddBindings(*it);

		mPool.Create(_device, infos);
	}
	
	void Material::DestroyDescriptorPool(const Device& _device)
	{
		mPool.Destroy(_device);
	}


	void Material::CreateDescriptorSetLayouts(const Device& _device, const RenderPipelineLayoutDescriptor& _pipLayout)
	{
		mLayouts.reserve(_pipLayout.bindSetDescs.size());

		for (auto it = _pipLayout.bindSetDescs.begin(); it != _pipLayout.bindSetDescs.end(); ++it)
		{
			DescriptorSetLayout& layout = mLayouts.emplace_back();
			layout.Create(_device, *it);
		}
	}
	
	void Material::DestroyDescriptorSetLayouts(const Device& _device)
	{
		for (auto it = mLayouts.begin(); it != mLayouts.end(); ++it)
			it->Destroy(_device);

		mLayouts.clear();
	}


	void Material::Create(const Device& _device, const RenderPipelineLayoutDescriptor& _pipLayout)
	{
		CreateDescriptorPool(_device, _pipLayout);
		CreateDescriptorSetLayouts(_device, _pipLayout);

		mSets = mPool.Allocate(_device, mLayouts);

		SA_LOG("Material created.", Infos, SA/Engine/Render/Vulkan);
	}

	void Material::Destroy(const Device& _device)
	{
		// No need to be called: DescriptorPool Destroy already free memory.
		// mPool.Free(_device, mSets);
		mSets.clear();

		DestroyDescriptorPool(_device);
		DestroyDescriptorSetLayouts(_device);

		SA_LOG("Material destroyed.", Infos, SA/Engine/Render/Vulkan);
	}
}
