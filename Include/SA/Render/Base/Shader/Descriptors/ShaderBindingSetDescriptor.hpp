// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_BINDING_SET_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SHADER_BINDING_SET_DESCRIPTOR_GUARD

#include <vector>

#include <SA/Render/Base/Shader/Descriptors/ShaderBindingDescriptor.hpp>

namespace Sa
{
	struct ShaderBindingSetDescriptor
	{
		/// List of registered binding for set.
		std::vector<ShaderBindingDescriptor> bindings;
	};


	namespace Serialize
	{
		void ToBinary(const ShaderBindingSetDescriptor& _obj, std::string& _str);
		void FromBinary(ShaderBindingSetDescriptor& _obj, class Reader& _read);
	}
}

#endif // GUARD
