// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SHADER_DESCRIPTOR_GUARD

#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderStage.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderVertexLayoutDescriptor.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderBindingSetDescriptor.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderPushConstantDescriptor.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderSpecConstantDescriptor.hpp>

namespace SA
{
	struct ShaderDescriptor
	{
		ShaderStage stage = ShaderStage::Unknown;

		ShaderVertexLayoutDescriptor vertexLayout;

		std::vector<ShaderBindingSetDescriptor> bindingSet;
		std::vector<ShaderPushConstantDescriptor> pushConstants;
		std::vector<ShaderSpecConstantDescriptor> specConstants;


		ShaderBindingDescriptor& EmplaceBinding(uint32_t _set);

		void Clear();
	};
}

#endif // GUARD
