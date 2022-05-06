// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_BINDING_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SHADER_BINDING_DESCRIPTOR_GUARD

#include <string>

#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderBindingType.hpp>

namespace Sa
{
	struct ShaderBindingDescriptor
	{
		/// Binding name (as written in shader).
		std::string name;

		/// Binding <b>data type</b> (struct) name (as written in shader).
		std::string dataTypeName;


		/// Type of binding.
		ShaderBindingType type = ShaderBindingType::UniformBuffer;


		/// Binding index in shader.
		uint32_t binding = 0u;

		/// Number of elements (array).
		uint32_t num = 1u;


		/// Input Attachment index (valid only if type == InputAttachment).
		uint32_t inAttachIndex = ~uint32_t();
	};
}

#endif // GUARD
