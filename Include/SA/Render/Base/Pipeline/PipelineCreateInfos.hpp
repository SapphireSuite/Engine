// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PIPELINE_CREATE_INFOS_GUARD
#define SAPPHIRE_RENDER_PIPELINE_CREATE_INFOS_GUARD

#include <SA/Render/Base/Pass/ARenderPass.hpp>

#include <SA/Render/Base/Shader/AShader.hpp>
#include <SA/Render/Base/Shader/ShaderStage.hpp>
#include <SA/Render/Base/Shader/ShaderBindingType.hpp>

#include <SA/Render/Base/Mesh/Vertex/VertexBindingLayout.hpp>

#include <SA/Render/Base/Pipeline/CullingMode.hpp>
#include <SA/Render/Base/Pipeline/FrontFaceMode.hpp>
#include <SA/Render/Base/Pipeline/PolygonMode.hpp>

namespace Sa
{
	struct PipelineShaderInfos
	{
		const AShader* shader = nullptr;
		const ShaderStage stage = ShaderStage::Unknown;
	};


	struct PipelineBindingInfos
	{
		uint32 binding = 0u;

		Flags<ShaderStage> stageFlags = ShaderStage::Unknown;

		ShaderBindingType type = ShaderBindingType::UniformBuffer;

		// Number of elements (array).
		uint32 num = 1u;
	};


	struct PipelineRenderModes
	{
		PolygonMode polygon = PolygonMode::Fill;
		CullingMode culling = CullingMode::Back;
		FrontFaceMode frontFace = FrontFaceMode::Clockwise;
	};


	struct PipelineCreateInfos
	{
		VertexBindingLayout vertexBindingLayout;

		std::vector<PipelineShaderInfos> shaders;
		std::vector<PipelineBindingInfos> bindings;

		PipelineRenderModes modes;

		const ARenderPass& renderPass;
		const RenderPassDescriptor& renderPassDesc;

		// Index of the associated subpass.
		uint32 subPassIndex = 0u;

		PipelineCreateInfos(const ARenderPass& _renderPass, const RenderPassDescriptor& _renderPassDesc) noexcept;

		// Helper functions.
		void AddBinding(PipelineBindingInfos _bindingInfos);
		void RemoveBinding(uint32 _binding);
	};
}

#endif // GUARD
