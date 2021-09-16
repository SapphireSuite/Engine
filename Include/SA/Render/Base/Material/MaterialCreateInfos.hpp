// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_MATERIAL_CREATE_INFOS_GUARD
#define SAPPHIRE_RENDER_MATERIAL_CREATE_INFOS_GUARD

#include <SA/Render/Base/Pipeline/APipeline.hpp>
#include <SA/Render/Base/Material/Bindings/AMaterialBinding.hpp>

namespace Sa
{
	struct MaterialCreateInfos
	{
		const APipeline& pipeline;
		const uint32 descriptorSetNum = 1u;

		std::vector<AMaterialBinding*> bindings;


		~MaterialCreateInfos();

		template <typename T, typename... Args>
		void AddBinding(Args&&... _args);
	};
}

#include <SA/Render/Base/Material/MaterialCreateInfos.inl>

#endif // GUARD
