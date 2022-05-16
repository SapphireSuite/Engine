// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PIPELINE_RENDER_PASS_INFOS_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_RENDER_PASS_INFOS_GUARD

#include <SA/Engine/Render/Base/Pass/ARenderPass.hpp>

namespace SA
{
	struct PipelineRenderPassInfos
	{
		/// Associated renderpass.
		const ARenderPass* renderPass = nullptr;

		/// Descriptor of the bound subpass of the renderpass.
		SubPassDescriptor subPassDesc;

		/// Index of the associated subpass.
		uint32_t subPassIndex = 0u;

		void SetRenderPass(const ARenderPass* _renderPass, const RenderPassDescriptor& _renderPassDesc, uint32_t _subPassIndex = 0u);
	};
}

#endif // GUARD
