// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DESCRIPTOR_SET_CREATE_INFOS_GUARD
#define SAPPHIRE_RENDER_DESCRIPTOR_SET_CREATE_INFOS_GUARD

#include <SA/Render/Base/Shader/Bindings/AShaderBinding.hpp>

namespace Sa
{
	class ARenderPipeline;

	struct DescriptorSetCreateInfos
	{
		const ARenderPipeline& pipeline;
		//const uint32 descriptorSetNum = 1u;

		std::vector<AShaderBinding*> bindings;


		~DescriptorSetCreateInfos();

		template <typename T, typename... Args>
		T* AddBinding(Args&&... _args);
	};
}

#include <SA/Render/Base/Pipeline/DescriptorSets/DescriptorSetCreateInfos.inl>

#endif // GUARD
