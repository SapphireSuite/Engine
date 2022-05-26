// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Material/VkMaterial.hpp>
#include <Render/Vulkan/Material/VkMaterialBindRecorder.hpp>

#include <HI/Cast.hpp>

#include <Render/Base/Pipeline/Descriptors/PipelineLayoutDescriptor.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Texture/VkTexture.hpp>

namespace SA::VK
{
	void Material::CreateDescriptorPool(const Device& _device, const PipelineLayoutDescriptor& _pipLayoutDesc)
	{
		DescriptorPoolInfos infos;
		infos.setNum = (uint32_t)_pipLayoutDesc.bindSetDescs.size();

		for (auto it = _pipLayoutDesc.bindSetDescs.begin(); it != _pipLayoutDesc.bindSetDescs.end(); ++it)
			infos.AddBindings(*it);

		mPool.Create(_device, infos);
	}
	
	void Material::DestroyDescriptorPool(const Device& _device)
	{
		mPool.Destroy(_device);
	}


	void Material::Create(const Device& _device,
		const PipelineLayout& _pipLayout,
		const PipelineLayoutDescriptor& _pipLayoutDesc,
		const MaterialBindingData& _bindData)
	{
		ARenderMaterial::Create(_pipLayoutDesc);

		CreateDescriptorPool(_device, _pipLayoutDesc);

		mSets = mPool.Allocate(_device, _pipLayout.GetDescriptorSetLayouts());

		SA_LOG("Material created.", Infos, SA/Engine/Render/Vulkan);

		if(!_bindData.Empty())
			BindData(_device, _bindData);
	}

	void Material::Destroy(const Device& _device)
	{
		ARenderMaterial::Destroy();

		// No need to be called: DescriptorPool Destroy already free memory.
		// mPool.Free(_device, mSets);
		mSets.clear();

		DestroyDescriptorPool(_device);

		SA_LOG("Material destroyed.", Infos, SA/Engine/Render/Vulkan);
	}


	void Material::ParseBinding(MaterialBindRecorder& _rec, const MaterialStaticBindingInfos& _infos, ARenderMaterialBinding* _binding)
	{
		SA_ASSERT(OutOfArrayRange, SA/Engine/Render/Vulkan, _infos.set, mSets);
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _binding, L"Input binding nulltpr!");

		VkWriteDescriptorSet& descWrite = _rec.descWrites.emplace_back();
		descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descWrite.pNext = nullptr;
		descWrite.dstSet = mSets[_infos.set];
		descWrite.dstBinding = _infos.binding;
		descWrite.dstArrayElement = _infos.offset;

		_binding->FillVkDescriptorWrite(_rec, descWrite);
	}

	void Material::BindData(const Device& _device, const MaterialBindingData& _bindData)
	{
		MaterialBindRecorder rec;
		
		for(auto& pair : _bindData.staticBindings)
			ParseBinding(rec, pair.first, pair.second);

		for(auto& pair : _bindData.namedBindings)
		{
			MaterialStaticBindingInfos staticBind;

			if(GetStaticBindFromNamed(pair.first, staticBind))
				ParseBinding(rec, staticBind, pair.second);
		}

		rec.Submit(_device);
	}
}
