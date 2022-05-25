// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Material/Bindings/IBOBinding.hpp>

#if SA_VULKAN

	#include <HI/Cast.hpp>

	#include <Render/Vulkan/Texture/VkTexture.hpp>

#endif

namespace SA
{
	IBOBinding::IBOBinding(uint32_t _binding, uint32_t _set, const ATexture* _IBO) :
		ARenderMaterialBinding(_binding, _set),
		IBOs{ _IBO }
	{
	}
	
	IBOBinding::IBOBinding(uint32_t _binding, uint32_t _set, std::vector<const ATexture*> _IBOs) :
		ARenderMaterialBinding(_binding, _set),
		IBOs{ std::move(_IBOs) }
	{
	}


#if SA_VULKAN

	VkDescriptorType IBOBinding::GetVkDescriptorType() const noexcept
	{
		return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	}

	VkWriteDescriptorSet IBOBinding::MakeVkDescriptors(VK::DescriptorSetUpdater& _updater) const
	{
		std::vector<VkDescriptorImageInfo>& descs = _updater.imageDescs.emplace_back();

		for (auto it = IBOs.begin(); it != IBOs.end(); ++it)
			descs.emplace_back(CastRef<VK::Texture>(*it).CreateDescriptorImageInfo());

		VkWriteDescriptorSet descWrite{};
		descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descWrite.pNext = nullptr;
		descWrite.dstSet = _updater.sets[set];
		descWrite.dstBinding = binding;
		descWrite.descriptorCount = (uint32_t)descs.size();
		descWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descWrite.pImageInfo = descs.data();

		return descWrite;
	}

#endif
}
