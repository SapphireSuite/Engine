// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_UBO_BINDING_GUARD
#define SAPPHIRE_RENDER_SHADER_UBO_BINDING_GUARD

#include <SA/Render/Base/Shader/Bindings/AShaderBinding.hpp>

//#include <SA/Render/Base/Buffers/IUniformBuffer.hpp>

namespace Sa
{
	class ShaderUBOBinding : public AShaderBinding
	{
	public:
		//std::vector<const IUniformBuffer*> UBOs;


		//ShaderUBOBinding(uint32 _binding, const IUniformBuffer* _UBO, uint32 _set = 0u) noexcept;
		//ShaderUBOBinding(uint32 _binding, std::vector<const IUniformBuffer*> _UBOs, uint32 _set = 0u) noexcept;


#if SA_VULKAN

		VkDescriptorType GetVkDescriptorType() const noexcept override final;

		VkWriteDescriptorSet MakeVkDescriptors(
			std::list<std::vector<VkDescriptorBufferInfo>>& _bufferDescs,
			std::list<std::vector<VkDescriptorImageInfo>>& _imageDescs) const override final;

#endif
	};
}

#endif // GUARD
