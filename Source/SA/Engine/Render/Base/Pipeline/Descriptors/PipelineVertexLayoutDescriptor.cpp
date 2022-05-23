// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Descriptors/PipelineVertexLayoutDescriptor.hpp>

#include <Render/Base/Shader/Descriptors/ShaderVertexLayoutDescriptor.hpp>

namespace SA
{
	PipelineVertexLayoutDescriptor& PipelineVertexLayoutDescriptor::operator=(const ShaderVertexLayoutDescriptor& _shDesc)
	{
		locations.assign(_shDesc.locations.begin(), _shDesc.locations.end());

		return *this;
	}
}
