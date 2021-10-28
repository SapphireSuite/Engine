// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PIPELINE_SHADER_INFOS_GUARD
#define SAPPHIRE_RENDER_PIPELINE_SHADER_INFOS_GUARD

#include <set>

//#include <SA/Render/Base/Shader/AShader.hpp>
#include <SA/Render/Base/Shader/ShaderDescriptor.hpp>
#include <SA/Render/Base/Shader/SpecConstants/SpecConstant.hpp>

#include <SA/Render/Base/Mesh/Vertex/VertexBindingLayout.hpp>

namespace Sa
{
	struct PipelineShaderStage
	{
		//const AShader* shader = nullptr;

		ShaderStage stage = ShaderStage::Unknown;
	};


	struct PipelineBindingDescriptor : public ShaderBindingDescriptor
	{
		Flags<ShaderStage> stageFlags;
	};

	struct PipelineBindingSetDescriptor
	{
		/// List of registered binding for set.
		std::vector<PipelineBindingDescriptor> bindings;
	};


	struct PipelineSpecConstant : public SpecConstantDescriptor
	{
		std::unique_ptr<SpecConstantBase> value;
	};

	struct PipelineShaderInfos
	{
		VertexBindingLayout vertexBindingLayout;

		std::vector<PipelineShaderStage> stages;

		PipelineBindingSetDescriptor userBindingSet;
		std::set<uint32> engineBindingSets;

		std::set<PipelineSpecConstant> userSpecConstants;
		std::set<SpecConstantDescriptor> engineSpecConstants; // Values set in engine.

		//void AddShader(const AShader* _shader, const ShaderDescriptor& _descriptor);


		template <typename T>
		void SetSpecConstant(uint32 _id, const T& _value);

		template <typename T>
		void SetSpecConstant(const std::string& _name, const T& _value);
	};
}

#include <SA/Render/Base/Pipeline/PipelineShaderInfos.inl>

#endif // GUARD
