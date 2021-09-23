// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/PipelineCreateInfos.hpp>

namespace Sa
{
	PipelineCreateInfos::PipelineCreateInfos(const ARenderPass& _renderPass, const RenderPassDescriptor& _renderPassDesc) noexcept :
		renderPass{ _renderPass },
		renderPassDesc{ _renderPassDesc }
	{
	}

	void PipelineCreateInfos::AddShader(const AShader& _shader, ShaderDescriptor _descriptor)
	{
		if (_descriptor.stage == ShaderStage::Vertex)
			vertexBindingLayout.desiredLayout = VertexLayout::Make(static_cast<VertexComp>((uint8)_descriptor.vertexLayout)); // TODO: Clean.

		PipelineShaderInfos& infos = shaders.emplace_back();
		infos.shader = &_shader;
		infos.descriptor = std::move(_descriptor);
		//shaders.emplace_back(&_shader, std::move(_descriptor));
	}
}
