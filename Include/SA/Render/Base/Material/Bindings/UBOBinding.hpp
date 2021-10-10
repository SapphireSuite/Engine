// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_UBO_BINDING_GUARD
#define SAPPHIRE_RENDER_UBO_BINDING_GUARD

#include <SA/Render/Base/Material/Bindings/ARenderMaterialBinding.hpp>

namespace Sa
{
	class ARenderBufferBase;

	class UBOBinding : public ARenderMaterialBinding
	{
	public:
		std::vector<const ARenderBufferBase*> UBOs;

		UBOBinding(uint32 _binding, const ARenderBufferBase* _UBO) noexcept;
		UBOBinding(uint32 _binding, std::vector<const ARenderBufferBase*> _UBOs) noexcept;


#if SA_VULKAN

		VkDescriptorType GetVkDescriptorType() const noexcept override final;

		VkWriteDescriptorSet MakeVkDescriptors(
			std::list<std::vector<VkDescriptorBufferInfo>>& _bufferDescs,
			std::list<std::vector<VkDescriptorImageInfo>>& _imageDescs) const override final;

#endif
	};
}

#endif // GUARD
