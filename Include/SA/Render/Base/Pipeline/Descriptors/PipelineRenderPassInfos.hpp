// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PIPELINE_RENDER_PASS_INFOS_GUARD
#define SAPPHIRE_RENDER_PIPELINE_RENDER_PASS_INFOS_GUARD

#include <SA/Render/Base/Pass/ARenderPass.hpp>

namespace Sa
{
	struct PipelineRenderPassInfos
	{
		/// Associated renderpass.
		const ARenderPass* renderPass = nullptr;

		/// Descriptor of the bound subpass of the renderpass.
		SubPassDescriptor subPassDesc;

		/// Index of the associated subpass.
		uint32 subPassIndex = 0u;

		void SetRenderPass(const ARenderPass* _renderPass, const RenderPassDescriptor& _renderPassDesc, uint32 _subPassIndex = 0u);
	};
}

#endif // GUARD
