// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/Base/Pipeline/PipelineShaderInfos.hpp>

namespace Sa
{
	void EmplaceBinding(PipelineBindingSetDescriptor& _bindSet, const ShaderBindingDescriptor& _binding, ShaderStage _stage)
	{
		PipelineBindingDescriptor* pipBindDesc = nullptr;

		// Search existing binding.
		for (auto& itpipBind : _bindSet.bindings)
		{
			if (itpipBind.binding == _binding.binding)
				pipBindDesc = &itpipBind;
		}

		if (!pipBindDesc)
			pipBindDesc = &_bindSet.bindings.emplace_back(_binding);

		pipBindDesc->stageFlags |= _stage;
	}

	//void PipelineShaderInfos::AddShader(const AShader* _shader, const ShaderDescriptor& _descriptor)
	//{
	//	if (_descriptor.stage == ShaderStage::Vertex)
	//		vertexBindingLayout.desiredLayout = VertexLayout::Make(static_cast<VertexComp>((uint8)_descriptor.vertexLayout)); // TODO: Clean.

	//	PipelineShaderStage& stage = stages.emplace_back();
	//	stage.shader = _shader;
	//	stage.stage = _descriptor.stage;


	//	//// Bindings
	//	//{
	//	//	for (auto& bindSet : _descriptor.userBindingSet.bindings)
	//	//		EmplaceBinding(userBindingSet, bindSet, _descriptor.stage);

	//	//	engineBindingSets.insert(_descriptor.engineBindingSets.begin(), _descriptor.engineBindingSets.end());
	//	//}


	//	//// Spec constants.
	//	//{
	//	//	// User
	//	//	for (auto& specCst : _descriptor.userSpecConstants)
	//	//		userSpecConstants.emplace(specCst);

	//	//	for (auto& specCst : _descriptor.engineSpecConstants)
	//	//		engineSpecConstants.emplace(specCst);
	//	//}
	//}
}
