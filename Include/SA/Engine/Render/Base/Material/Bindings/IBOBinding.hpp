// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_IBO_BINDING_GUARD
#define SAPPHIRE_ENGINE_IBO_BINDING_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Material/Bindings/ARenderMaterialBinding.hpp>

namespace SA
{
	class ATexture;

	class IBOBinding : public ARenderMaterialBinding
	{
	public:
		std::vector<const ATexture*> IBOs;

		IBOBinding() = default;
		IBOBinding(uint32_t _binding, uint32_t _set, const ATexture* _IBO);
		IBOBinding(uint32_t _binding, uint32_t _set, std::vector<const ATexture*> _IBOs);


	#if SA_VULKAN

		VkDescriptorType GetVkDescriptorType() const noexcept override final;
	
		VkWriteDescriptorSet MakeVkDescriptors(VK::DescriptorSetUpdater& _updater) const override final;

	#endif
	};
}

#endif // GUARD
