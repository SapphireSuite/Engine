// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Material/Bindings/UBOBinding.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Base/Buffers/ARenderBufferBase.hpp>
#include <Render/Vulkan/Buffers/IVkBufferBinding.hpp>

namespace Sa
{
	UBOBinding::UBOBinding(uint32 _binding, const ARenderBufferBase* _UBO) noexcept :
		ARenderMaterialBinding(_binding),
		UBOs{ _UBO }
	{
	}
	
	UBOBinding::UBOBinding(uint32 _binding, std::vector<const ARenderBufferBase*> _UBOs) noexcept :
		ARenderMaterialBinding(_binding),
		UBOs{ std::move(_UBOs) }
	{
	}


#if SA_VULKAN

	VkDescriptorType UBOBinding::GetVkDescriptorType() const noexcept
	{
		return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	}

	VkWriteDescriptorSet UBOBinding::MakeVkDescriptors(
		std::list<std::vector<VkDescriptorBufferInfo>>& _bufferDescs,
		std::list<std::vector<VkDescriptorImageInfo>>& _imageDescs) const
	{
		(void)_imageDescs;

		std::vector<VkDescriptorBufferInfo>& descs = _bufferDescs.emplace_back();

		for (auto it = UBOs.begin(); it != UBOs.end(); ++it)
			descs.push_back((*it)->As<Vk::IBufferBinding>().CreateDescriptorBufferInfo());


		VkWriteDescriptorSet descWrite{};
		descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descWrite.pNext = nullptr;

		// Set by VkMaterial.
		// descWrite.dstSet = 

		descWrite.dstBinding = binding;
		descWrite.descriptorCount = SizeOf<uint32>(descs);
		descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descWrite.pBufferInfo = descs.data();

		return descWrite;
	}

#endif
}
