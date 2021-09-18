// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Bindings/ShaderUBOBinding.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Buffers/VkBufferBase.hpp>

namespace Sa
{
	ShaderUBOBinding::ShaderUBOBinding(uint32 _binding, const IUniformBuffer* _UBO, uint32 _descriptor) noexcept :
		AShaderBinding(_binding, _descriptor),
		UBOs{ _UBO }
	{
	}

	ShaderUBOBinding::ShaderUBOBinding(uint32 _binding, std::vector<const IUniformBuffer*> _UBOs, uint32 _descriptor) noexcept :
		AShaderBinding(_binding, _descriptor),
		UBOs{ std::move(_UBOs) }
	{
	}


#if SA_VULKAN

	VkDescriptorType ShaderUBOBinding::GetVkDescriptorType() const noexcept
	{
		return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	}

	VkWriteDescriptorSet ShaderUBOBinding::MakeVkDescriptors(
		std::list<std::vector<VkDescriptorBufferInfo>>& _bufferDescs,
		std::list<std::vector<VkDescriptorImageInfo>>& _imageDescs) const
	{
		(void)_imageDescs;

		std::vector<VkDescriptorBufferInfo>& descs = _bufferDescs.emplace_back();

		for (auto it = UBOs.begin(); it != UBOs.end(); ++it)
			descs.push_back((*it)->As<Vk::BufferBase>().CreateDescriptorBufferInfo());


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
