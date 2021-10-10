// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_IBO_BINDING_GUARD
#define SAPPHIRE_RENDER_IBO_BINDING_GUARD

#include <SA/Render/Base/Material/Bindings/ARenderMaterialBinding.hpp>

namespace Sa
{
	class ATexture;

	class IBOBinding : public ARenderMaterialBinding
	{
	public:
		std::vector<const ATexture*> IBOs;

		IBOBinding(uint32 _binding, const ATexture* _IBO) noexcept;
		IBOBinding(uint32 _binding, std::vector<const ATexture*> _IBOs) noexcept;


#if SA_VULKAN

		VkDescriptorType GetVkDescriptorType() const noexcept override final;

		VkWriteDescriptorSet MakeVkDescriptors(
			std::list<std::vector<VkDescriptorBufferInfo>>& _bufferDescs,
			std::list<std::vector<VkDescriptorImageInfo>>& _imageDescs) const override final;

#endif
	};
}

#endif // GUARD
