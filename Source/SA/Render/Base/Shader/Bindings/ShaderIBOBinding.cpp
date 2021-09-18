// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Bindings/ShaderIBOBinding.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Texture/VkTexture.hpp>

namespace Sa
{
	ShaderIBOBinding::ShaderIBOBinding(uint32 _binding, const ATexture* _IBO, uint32 _descriptor) noexcept :
		AShaderBinding(_binding, _descriptor),
		IBOs{ _IBO }
	{
	}

	ShaderIBOBinding::ShaderIBOBinding(uint32 _binding, std::vector<const ATexture*> _IBOs, uint32 _descriptor) noexcept :
		AShaderBinding(_binding, _descriptor),
		IBOs{ std::move(_IBOs) }
	{
	}


#if SA_VULKAN

	VkDescriptorType ShaderIBOBinding::GetVkDescriptorType() const noexcept
	{
		return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	}

	VkWriteDescriptorSet ShaderIBOBinding::MakeVkDescriptors(
		std::list<std::vector<VkDescriptorBufferInfo>>& _bufferDescs,
		std::list<std::vector<VkDescriptorImageInfo>>& _imageDescs) const
	{
		(void)_bufferDescs;

		std::vector<VkDescriptorImageInfo>& descs = _imageDescs.emplace_back();

		for (auto it = IBOs.begin(); it != IBOs.end(); ++it)
			descs.push_back((*it)->As<Vk::Texture>().CreateDescriptorImageInfo());


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
