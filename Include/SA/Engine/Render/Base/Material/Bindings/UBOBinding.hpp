// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_UBO_BINDING_GUARD
#define SAPPHIRE_ENGINE_UBO_BINDING_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Material/Bindings/ARenderMaterialBinding.hpp>

namespace SA
{
	class UBOBinding : public ARenderMaterialBinding
	{
	public:
		// std::vector<const *> UBOs;

		UBOBinding() = default;
		// UBOBinding(uint32_t _binding, uint32_t _set, const * _IBO);
		// UBOBinding(uint32_t _binding, uint32_t _set, std::vector<const *> _IBOs);


	#if SA_VULKAN

		VkDescriptorType GetVkDescriptorType() const noexcept override final;
	
	#endif
	};
}

#endif // GUARD
