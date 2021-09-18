// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DESCRIPTOR_SET_CREATE_INFOS_GUARD
#define SAPPHIRE_RENDER_DESCRIPTOR_SET_CREATE_INFOS_GUARD

#include <SA/Render/Base/Shader/Bindings/AShaderBinding.hpp>

namespace Sa
{
	class APipeline;

	struct DescriptorSetCreateInfos
	{
		const APipeline& pipeline;
		const uint32 descriptorSetNum = 1u;

		std::vector<AShaderBinding*> bindings;


		~DescriptorSetCreateInfos();

		template <typename T, typename... Args>
		void AddBinding(Args&&... _args);
	};
}

#include <SA/Render/Base/Pipeline/DescriptorSets/DescriptorSetCreateInfos.inl>

#endif // GUARD
