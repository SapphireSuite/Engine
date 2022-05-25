// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_BINDING_SET_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SHADER_BINDING_SET_DESCRIPTOR_GUARD

#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderBindingDescriptor.hpp>

namespace SA
{
	struct ShaderBindingSetDescriptor
	{
		/// List of registered binding for set.
		std::vector<ShaderBindingDescriptor> bindings;
	};


	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderBindingSetDescriptor& _desc, std::string& _dst);

		template <>
		bool FromBinary(ShaderBindingSetDescriptor& _desc, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD
