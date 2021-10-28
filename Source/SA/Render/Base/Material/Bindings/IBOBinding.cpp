// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Material/Bindings/IBOBinding.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Texture/VkTexture.hpp>

namespace Sa
{
	IBOBinding::IBOBinding(uint32 _binding, const ATexture* _IBO) noexcept :
		ARenderMaterialBinding(_binding),
		IBOs{ _IBO }
	{
	}
	
	IBOBinding::IBOBinding(uint32 _binding, std::vector<const ATexture*> _IBOs) noexcept :
		ARenderMaterialBinding(_binding),
		IBOs{ std::move(_IBOs) }
	{
	}


#if SA_VULKAN

	VkDescriptorType IBOBinding::GetVkDescriptorType() const noexcept
	{
		return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	}

	VkWriteDescriptorSet IBOBinding::MakeVkDescriptors(
		std::list<std::vector<VkDescriptorBufferInfo>>& _bufferDescs,
		std::list<std::vector<VkDescriptorImageInfo>>& _imageDescs) const
	{
		(void)_bufferDescs;

		std::vector<VkDescriptorImageInfo>& descs = _imageDescs.emplace_back();

		//for (auto it = IBOs.begin(); it != IBOs.end(); ++it)
		//	descs.push_back((*it)->As<Vk::Texture>().CreateDescriptorImageInfo());


		VkWriteDescriptorSet descWrite{};
		descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descWrite.pNext = nullptr;

		// Set by VkMaterial.
		// descWrite.dstSet = 

		descWrite.dstBinding = binding;
		descWrite.descriptorCount = SizeOf<uint32>(descs);
		descWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descWrite.pImageInfo = descs.data();

		return descWrite;
	}

#endif
}
