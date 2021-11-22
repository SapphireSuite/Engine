// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Descriptors/PipelineBindingSetDescriptor.hpp>

namespace Sa
{
	PipelineBindingSetDescriptor PipelineBindingSetDescriptor::modelBindSetDesc = []()
	{
		PipelineBindingSetDescriptor res;

		auto& trBind = res.bindings.emplace_back();
		trBind.binding = 0u;
		trBind.type = ShaderBindingType::StorageBuffer;
		trBind.stageFlags = ShaderStage::Vertex;

		auto& normalBind = res.bindings.emplace_back();
		normalBind.binding = 1u;
		normalBind.type = ShaderBindingType::StorageBuffer;
		normalBind.stageFlags = ShaderStage::Vertex;

		return res;
	}();

	PipelineBindingSetDescriptor PipelineBindingSetDescriptor::cameraBindSetDesc = []()
	{
		PipelineBindingSetDescriptor res;

		auto& bind = res.bindings.emplace_back();
		bind.type = ShaderBindingType::StorageBuffer;
		bind.stageFlags = ShaderStage::Vertex;

		return res;
	}();
}
