// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_BINDING_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SHADER_BINDING_DESCRIPTOR_GUARD

#include <string>

#include <SA/Render/Base/Shader/Bindings/ShaderBindingType.hpp>

namespace Sa
{
	struct ShaderBindingDescriptor
	{
		/// Binding name (as written in shader).
		std::string name;


		// Block serialize


		/// Type of binding.
		ShaderBindingType type = ShaderBindingType::UniformBuffer;


		/// Binding index in shader.
		uint32 binding = 0u;

		/// Number of elements (array).
		uint32 num = 1u;


		/// Input Attachment index (valid only if type == InputAttachment).
		uint32 inAttachIndex = ~uint32();
	};


	namespace Serialize
	{
		void ToBinary(const ShaderBindingDescriptor& _obj, std::string& _str);
		void FromBinary(ShaderBindingDescriptor& _obj, class Reader& _read);
	}
}

#endif // GUARD
