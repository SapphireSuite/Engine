// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_MATERIAL_CREATE_INFOS_GUARD
#define SAPPHIRE_RENDER_MATERIAL_CREATE_INFOS_GUARD

#include <SA/Core/Types/Int.hpp>

#include <SA/Render/Base/Material/Bindings/UBOBinding.hpp>
#include <SA/Render/Base/Material/Bindings/IBOBinding.hpp>

namespace Sa
{
	class ARenderPipeline;
	struct RenderPipelineDescriptor;

	struct RenderMaterialCreateInfos
	{
		const ARenderPipeline* pipeline = nullptr;
		const RenderPipelineDescriptor* desc = nullptr;
		uint32 setIndex = 0;

		std::vector<const ARenderMaterialBinding*> bindings;

		~RenderMaterialCreateInfos();

		template <typename BindT, typename... Args>
		void AddBinding(Args&&... _args);
	};
}

#include <SA/Render/Base/Material/RenderMaterialCreateInfos.inl>

#endif // GUARD
