// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PIPELINE_SHADER_INFOS_GUARD
#define SAPPHIRE_RENDER_PIPELINE_SHADER_INFOS_GUARD

#include <set>

#include <SA/Render/Base/Shader/AShader.hpp>
#include <SA/Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

#include <SA/Render/Base/Mesh/Vertex/VertexBindingLayout.hpp>

#include <SA/Render/Base/Pipeline/SpecConstant.hpp>

namespace Sa
{
	struct PipelineShaderStage
	{
		const AShader* shader = nullptr;

		ShaderStage stage = ShaderStage::Unknown;
	};


	struct PipelineBindingDescriptor : public ShaderBindingDescriptor
	{
		Flags<ShaderStage> stageFlags;
	};

	struct PipelineBindingSetDescriptor
	{
		/// List of registered bindings for set.
		std::vector<PipelineBindingDescriptor> bindings;
	};


	struct PipelinePushConstantDescriptor : public ShaderPushConstantDescriptor
	{
		Flags<ShaderStage> stageFlags;
	};


	struct PipelineSpecConstant : public ShaderSpecConstantDescriptor
	{
		std::unique_ptr<SpecConstantBase> value;
	};


	struct PipelineShaderInfos
	{
		VertexBindingLayout vertexBindingLayout;

		std::vector<PipelineShaderStage> stages;

		std::vector<PipelineBindingSetDescriptor> bindingSets;

		std::vector<PipelinePushConstantDescriptor> pushConstants;
		std::set<PipelineSpecConstant> specConstants;

		void AddShader(const AShader* _shader, const ShaderDescriptor& _desc);


		template <typename T>
		void SetSpecConstant(uint32 _id, const T& _value);

		template <typename T>
		void SetSpecConstant(const std::string& _name, const T& _value);
	};
}

#include <SA/Render/Base/Pipeline/PipelineShaderInfos.inl>

#endif // GUARD
