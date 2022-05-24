// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

namespace SA
{
	ShaderBindingDescriptor& ShaderDescriptor::EmplaceBinding(uint32_t _set)
	{
		while (_set >= bindingSet.size())
			bindingSet.emplace_back();

		return bindingSet[_set].bindings.emplace_back();
	}

	void ShaderDescriptor::Clear()
	{
		stage = ShaderStage::Unknown;

		vertexLayout.Clear();

		bindingSet.clear();
		pushConstants.clear();
		specConstants.clear();
	}
}
