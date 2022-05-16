// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Descriptors/PipelineRenderPassInfos.hpp>

#include <SA/Collections/Debug>

namespace SA
{
	void PipelineRenderPassInfos::SetRenderPass(const ARenderPass* _renderPass,
		const RenderPassDescriptor& _renderPassDesc,
		uint32_t _subPassIndex)
	{
		renderPass = _renderPass;
		subPassIndex = _subPassIndex;

		SA_ASSERT(OutOfRange, SA/Engine/Render/Vulkan, _subPassIndex, 0u, (uint32_t)_renderPassDesc.subPassDescs.size(), 
			L"Pipeline SubPass index out of RenderPass SubPassDescriptor range!");

		subPassDesc = _renderPassDesc.subPassDescs[_subPassIndex];
	}
}