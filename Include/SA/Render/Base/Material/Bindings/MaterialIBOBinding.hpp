// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_MATERIAL_IBO_BINDING_GUARD
#define SAPPHIRE_RENDER_MATERIAL_IBO_BINDING_GUARD

#include <SA/Render/Base/Material/Bindings/AMaterialBinding.hpp>

#include <SA/Render/Base/Texture/ATexture.hpp>

namespace Sa
{
	class MaterialIBOBinding : public AMaterialBinding
	{
	public:
		std::vector<const ATexture*> IBOs;


		MaterialIBOBinding(uint32 _binding, const ATexture* _IBO, uint32 _descriptor = ~uint32()) noexcept;
		MaterialIBOBinding(uint32 _binding, std::vector<const ATexture*> _IBOs, uint32 _descriptor = ~uint32()) noexcept;


#if SA_VULKAN

		VkDescriptorType GetVkDescriptorType() const noexcept override final;

		VkWriteDescriptorSet MakeVkDescriptors(
			std::list<std::vector<VkDescriptorBufferInfo>>& _bufferDescs,
			std::list<std::vector<VkDescriptorImageInfo>>& _imageDescs) const override final;

#endif
	};
}

#endif // GUARD
