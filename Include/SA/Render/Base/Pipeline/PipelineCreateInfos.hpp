// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PIPELINE_CREATE_INFOS_GUARD
#define SAPPHIRE_RENDER_PIPELINE_CREATE_INFOS_GUARD

#include <SA/Render/Base/Pass/ARenderPass.hpp>

#include <SA/Render/Base/Shader/AShader.hpp>
#include <SA/Render/Base/Shader/ShaderDescriptor.hpp>

#include <SA/Render/Base/Mesh/Vertex/VertexBindingLayout.hpp>

#include <SA/Render/Base/Pipeline/CullingMode.hpp>
#include <SA/Render/Base/Pipeline/FrontFaceMode.hpp>
#include <SA/Render/Base/Pipeline/PolygonMode.hpp>

namespace Sa
{
	struct PipelineRenderModes
	{
		PolygonMode polygon = PolygonMode::Fill;
		CullingMode culling = CullingMode::Back;
		FrontFaceMode frontFace = FrontFaceMode::Clockwise;
	};

	struct PipelineShaderInfos
	{
		const AShader* shader;
		ShaderDescriptor descriptor;
	};

	struct PipelineCreateInfos
	{
//{ RenderPass

		/// Associated renderpass.
		const ARenderPass& renderPass;

		/// Descriptor of the bound renderpass.
		const RenderPassDescriptor& renderPassDesc;

		/// Index of the associated subpass.
		uint32 subPassIndex = 0u;

//}

		/// Rendering modes.
		PipelineRenderModes modes;


		VertexBindingLayout vertexBindingLayout;


		/// Used shaders + descriptors.
		std::vector<PipelineShaderInfos> shaders;


		PipelineCreateInfos(const ARenderPass& _renderPass, const RenderPassDescriptor& _renderPassDesc) noexcept;

		void AddShader(const AShader& _shader, ShaderDescriptor _descriptor);
	};
}

#endif // GUARD
