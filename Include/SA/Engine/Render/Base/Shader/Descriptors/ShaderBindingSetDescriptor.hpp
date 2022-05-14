// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_BINDING_SET_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SHADER_BINDING_SET_DESCRIPTOR_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderBindingDescriptor.hpp>

namespace SA
{
	struct ShaderBindingSetDescriptor
	{
		/// List of registered binding for set.
		std::vector<ShaderBindingDescriptor> bindings;
	};
}

#endif // GUARD
