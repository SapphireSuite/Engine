// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_MATERIAL_UBO_BINDING_GUARD
#define SAPPHIRE_RENDER_MATERIAL_UBO_BINDING_GUARD

#include <SA/Render/Base/Material/Bindings/AMaterialBinding.hpp>

#include <SA/Render/Base/Buffers/IUniformBuffer.hpp>

namespace Sa
{
	class MaterialUBOBinding : public AMaterialBinding
	{
	public:
		std::vector<const IUniformBuffer*> UBOs;


		MaterialUBOBinding(uint32 _binding, const IUniformBuffer* _UBO, uint32 _descriptor = ~uint32()) noexcept;
		MaterialUBOBinding(uint32 _binding, std::vector<const IUniformBuffer*> _UBOs, uint32 _descriptor = ~uint32()) noexcept;


#if SA_VULKAN

		VkDescriptorType GetVkDescriptorType() const noexcept override final;

		VkWriteDescriptorSet MakeVkDescriptors(
			std::list<std::vector<VkDescriptorBufferInfo>>& _bufferDescs,
			std::list<std::vector<VkDescriptorImageInfo>>& _imageDescs) const override final;

#endif
	};
}

#endif // GUARD
