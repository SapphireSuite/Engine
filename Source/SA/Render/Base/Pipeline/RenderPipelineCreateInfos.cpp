// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/RenderPipelineCreateInfos.hpp>

namespace Sa
{
	RenderPipelineCreateInfos::RenderPipelineCreateInfos(const ARenderPass* _renderPass, const RenderPassDescriptor& _renderPassDesc, uint32 _subPassIndex)
	{
		SetRenderPass(_renderPass, _renderPassDesc, _subPassIndex);
	}

	void RenderPipelineCreateInfos::SetRenderPass(const ARenderPass* _renderPass, const RenderPassDescriptor& _renderPassDesc, uint32 _subPassIndex)
	{
		renderPass = _renderPass;
		subPassIndex = _subPassIndex;

		SA_ASSERT(OutOfRange, SA/Render/Vulkan, _subPassIndex, 0u, (uint32)_renderPassDesc.subPassDescs.size(), 
			L"Pipeline SubPass index out of RenderPass SubPassDescriptor range!");

		subPassDesc = _renderPassDesc.subPassDescs[_subPassIndex];
	}

	void RenderPipelineCreateInfos::AddShader(const AShader* _shader, const ShaderDescriptor& _descriptor)
	{
		shaderInfos.AddShader(_shader, _descriptor);
	}
}
