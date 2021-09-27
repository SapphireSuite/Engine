// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDER_PIPELINE_CREATE_INFOS_GUARD
#define SAPPHIRE_RENDER_RENDER_PIPELINE_CREATE_INFOS_GUARD

#include <SA/Render/Base/Pass/ARenderPass.hpp>

#include <SA/Render/Base/Pipeline/PipelineRenderModes.hpp>
#include <SA/Render/Base/Pipeline/PipelineShaderInfos.hpp>

namespace Sa
{
	struct RenderPipelineCreateInfos
	{
//{ RenderPass

		/// Associated renderpass.
		const ARenderPass* renderPass = nullptr;

		/// Descriptor of the bound subpass of the renderpass.
		SubPassDescriptor subPassDesc;

		/// Index of the associated subpass.
		uint32 subPassIndex = 0u;

//}

		/// Rendering modes.
		PipelineRenderModes modes;


		/// Bound shader infos.
		PipelineShaderInfos shaderInfos;


		RenderPipelineCreateInfos() = default;
		RenderPipelineCreateInfos(const ARenderPass* _renderPass, const RenderPassDescriptor& _renderPassDesc, uint32 _subPassIndex = 0u);

		void SetRenderPass(const ARenderPass* _renderPass, const RenderPassDescriptor& _renderPassDesc, uint32 _subPassIndex = 0u);

		void AddShader(const AShader* _shader, const ShaderDescriptor& _descriptor);
	};
}

#endif // GUARD
